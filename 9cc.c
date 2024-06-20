#include<stdio.h>
#include<stdlib.h>


int main(int argc, char **argv)
{
	//もし引数が2つじゃなかったら
	if(argc != 2)
	{
		fprintf(stderr,"引数の個数が正しくありません\n");
		return 1;
	}

	char *p = argv[1]; //argv[1]のアドレスをポインタ変数pに格納
	
	//出力結果をリダイレクト時にアセンブリにできる用
	printf(".intel_syntax noprefix\n");
 	printf(".globl main\n");
        printf("main:\n");
	printf("  mov rax, %ld\n", strtol(p, &p, 10)); //atoiでは文字列をint型に直してくれるだけであり文字数は返してくれないので次の項をどれを読めばいいかわからなくなる。そのためstrtolを使用
						       
//strtolは数値を読み込んだあとポインタをアップデートする。つまりアドレス内の値が数値だったとき整数にして返すが
//文字列(今回だと + , -)だったときはアドレスのみが加算されて返ってくるのでそのアドレス内の値と- or + が一致すると加算する仕組みを作れば良い

	//*p回ループ
	while(*p)
	{
		//もしpアドレスの中身が+と一致するとき
		if(*p == '+')
		{
			p++;//pアドレスを加算(つまり次のアドレスを参照して)
			printf("  add rax, %ld\n", strtol(p, &p, 10)); //値を見に行く
      			continue;
		}
		
		//もしpアドレスの中身が-と一致するとき
		if (*p == '-') 
		{
      			p++;
      			printf("  sub rax, %ld\n", strtol(p, &p, 10));
      			continue;
   		}

    		fprintf(stderr, "予期しない文字です: '%c'\n", *p);
    		return 1;

	}

	  printf("  ret\n");
  	  return 0;
}
