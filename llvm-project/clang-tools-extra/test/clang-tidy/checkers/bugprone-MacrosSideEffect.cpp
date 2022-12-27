// RUN: %check_clang_tidy %s bugprone-MacrosSideEffect %t

typedef __typeof(sizeof(int*)) FILE_t;
typedef __typeof(sizeof(wchar_t))  wint_t;
FILE_t fopen(const char *,const char *);
FILE_t fptr ;
int getc(FILE_t);
wint_t getwc (FILE_t);
int putc(int,FILE_t);
wint_t putwc(int,FILE_t);
int c = 'a';
const char* file_name = "abc";
FILE_t b ;
FILE_t input;
FILE_t output;
#define stdin input
#define stdout output
#define sideeffect fopen("avbw", "r")
#define sideeffect1 (b = fopen("avbw", "r"))



FILE_t openfile(){
    return fopen("aa" , "w");
}
int errorGetC() {
  getc(fopen("avbbw", "r"));
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
  getc(b = fopen("avbw", "r")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
  getc(true?fopen("avbw", "r") : fopen("avbw", "w")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
  getc(false?fopen("avbw", "r") : fopen("avbw", "wr")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
  getc(openfile());
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
  getc(sideeffect);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
  getc(sideeffect1);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getc' might have a side effect [bugprone-MacrosSideEffect]
}

int errorGetwc(){
  getwc(fopen("avbbw", "r"));
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]
  getwc(b = fopen("avbw", "r")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]
  getwc(true?fopen("avbw", "r") : fopen("avbw", "w")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]
  getwc(false?fopen("avbw", "r") : fopen("avbw", "wr")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]
  getwc(openfile());
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]
  getwc(sideeffect);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]
  getwc(sideeffect1);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'getwc' might have a side effect [bugprone-MacrosSideEffect]  
}


int errorPutc(){
  putc(c,fopen("avbbw", "r"));
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c, fptr ? fptr :(fptr = fopen("abc", "w")));
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c,b = fopen("avbw", "r")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c, true?fopen("avbw", "r") : fopen("avbw", "w")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c,false?fopen("avbw", "r") : fopen("avbw", "wr")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c,openfile());
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c,sideeffect);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
  putc(c,sideeffect1);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putc' might have a side effect [bugprone-MacrosSideEffect]
}

int errorPutwc(){
  putwc(c,fopen("avbbw", "r"));
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c, fptr ? fptr :(fptr = fopen("abc", "w")));
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c,b = fopen("avbw", "r")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c, true?fopen("avbw", "r") : fopen("avbw", "w")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c,false?fopen("avbw", "r") : fopen("avbw", "wr")); 
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c,openfile());
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c,sideeffect);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
  putwc(c,sideeffect1);
  // CHECK-MESSAGES: :[[@LINE-1]]:3: warning: function 'putwc' might have a side effect [bugprone-MacrosSideEffect]
}



// FIXME: Add something that doesn't trigger the check here.
int noerror(){
getc(b);
getc(stdin);
getc(stdout);
getwc(b);
getwc(stdin);
getwc(stdout);
putc(c,b);
putc(c,stdin);
putc(c,stdout);
putwc(c,b);
putwc(c,stdin);
putwc(c,stdout);
}
