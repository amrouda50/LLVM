//===--- MacrossideeffectCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MacrossideeffectCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bugprone {

void MacrossideeffectCheck::registerMatchers(MatchFinder * Finder) {
  const int functionsCount = 4;
  llvm::SmallVector < std::string, functionsCount > platformDependantMacros = {
    "getc",
    "getwc",
    "putc",
    "putwc"
  };
  const auto GetCharacter = functionDecl(
    hasAnyName(platformDependantMacros[0], platformDependantMacros[1]));
  const auto PutCharacter = functionDecl(
    hasAnyName(platformDependantMacros[2], platformDependantMacros[3]));

  auto unlessPutGetChar = [](int amount = 1) {
    return hasArgument(
        amount,
        unless(declRefExpr(to(varDecl()))));
  };

  Finder -> addMatcher(
    callExpr(
      callee(
        GetCharacter.bind("charGet")
      ),
      unlessPutGetChar(0)
    ).bind("getCharacter")
    ,this);

  Finder -> addMatcher(
    callExpr(
      callee(
        PutCharacter.bind("charPut")
      ),
      unlessPutGetChar(1)
    ).bind("putCharacter")
    ,this);

}

void MacrossideeffectCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *GetCharacterMatchedDecl = Result.Nodes.getNodeAs<CallExpr>("getCharacter");
  const auto *GetCharacterFunctionName = Result.Nodes.getNodeAs<FunctionDecl>("charGet");
  const auto *PutCharacterMatchedDecl = Result.Nodes.getNodeAs<CallExpr>("putCharacter");
  const auto *PutCharacterFunctionName = Result.Nodes.getNodeAs<FunctionDecl>("charPut");

if(GetCharacterMatchedDecl){
 diag(GetCharacterMatchedDecl->getExprLoc() , "function %0 might have a side effect") << GetCharacterFunctionName;
 }

if(PutCharacterMatchedDecl){
   diag(PutCharacterMatchedDecl->getExprLoc() , "function %0 might have a side effect") << PutCharacterFunctionName;
}
  

}

} // namespace bugprone
} // namespace tidy
} // namespace clang
