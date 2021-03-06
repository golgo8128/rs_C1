#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"
static int upto; /* 上流何塩基まで表示するかを指定 */
static int down; /* 下流何塩基まで表示するかを指定 */
/* パラメータ処理 */
int trsite5_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-trsite5") == 0){
    upto = atoi(argv[n + 1]); 
    /* ２番目のパラメータを上流で表示する塩基数とする */
    down = atoi(argv[n + 2]);
    /* ３番目のパラメータを下流で表示する塩基数とする */
    return 3; 
  }
  else return 0;
}
void trsite5_head(char *line){
}
/* エントリ処理 */
void trsite5_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i, j, begin, end, k, dobe, doen, begins, ends, js, ks, dobes, doens;
  for(i = 0;i < ncds;i ++){ /* コード領域の数だけ処理を繰り返す(始) */
    if(valid_cds[i] == 0) { continue; }
    else if(cds[i].complement == 0 && cds[i].cds_start != 0){
      /* コード領域が二重鎖の反対側でなく、翻訳開始領域が明確(始) */
      begin = cds[i].cds_start - upto; /* 上流の表示開始地点 */
      end = cds[i].cds_start + 2;      /* 開始コドンの最後の塩基 */
      printf("%s %d ( %d -> %d ): ",cds[i].gene, i,cds[i].cds_start, cds[i].cds_end);
      /*      printf("%s\n", cds[i].product); */
      for(j = begin;j <= end;j ++){ /* 塩基を上流から開始コドンまで表示 */
	if(j >= 1 && j <= max)putchar(seqn[j-1]);
	else putchar('-'); /* データがないときは、-を表示 */
	if(j == cds[i].cds_start - 1)putchar(' ');
      }
      putchar(' ');
      dobe = cds[i].cds_start + 1; /* 下流の表示開始地点 */
      doen = cds[i].cds_start + down; /* 下流の表示最終地点 */
      for(k = dobe; k <= doen; k++){ /* 塩基を下流の始めから終わりまで表示 */
	if(k >= 1 && k<= max)putchar(seqn[k+1]);
	else putchar(' ');
      }
      putchar('\n');
    } /* コード領域が二重鎖の反対側でなく、翻訳開始領域が明確(終) */
    else if(cds[i].complement == 1 && cds[i].cds_end != 0){
      /* コード領域が二重鎖の反対側にある */
      begins = cds[i].cds_end + upto; /*相補鎖でいう上流翻訳開始地点*/
      ends = cds[i].cds_end - 2;      /* 相補鎖でいう開始コドンの最後の塩基 */
      printf("%d(%d <- %d):",i,cds[i].cds_start, cds[i].cds_end);
      printf("%s\n", cds[i].product);
      for(js = begins;js >= ends;js --){ /* 塩基を上流から開始コドンまで表示 */
	if(js >= 1 && js <= max){
	  if(seqn[js-1]=='a')	putchar('t');
	  if(seqn[js-1]=='t')	putchar('a');
	  if(seqn[js-1]=='c')	putchar('g');
	  if(seqn[js-1]=='g')	putchar('c');
	}
	else putchar('-'); /* データがないときは、-を表示 */
	if(js == cds[i].cds_end + 1)putchar(' '); 
      }
      putchar(' ');
      dobes = cds[i].cds_end -3 ; /* 相補鎖でいう下流の表示開始地点 */
      doens = cds[i].cds_end - down -2; /* 相補鎖でいう下流の表示最終地点 */
      for(ks = dobes; ks >= doens; ks--){/*塩基を下流の始めから終わりまで表示*/
	  if(ks >= 1 && ks<= max){
	    if(seqn[ks-1]=='a')	putchar('t');
	    if(seqn[ks-1]=='t')	putchar('a');
	    if(seqn[ks-1]=='c')	putchar('g');
	    if(seqn[ks-1]=='g')	putchar('c');	
	  }
	  else putchar(' ');
	}
      putchar('\n');
    }
    else printf(" ????? \n");
    /* putchar('\n'); */
  }
} /* コード領域の数だけ処理を繰り返す(終) */
/* 最終処理 */
void trsite5_fin(){
  /* printf("Finished!!\n"); */
}
/* ヘルプ */
void trsite5_help(){
  printf("-trsite5\t Displays sequences around translation initiation sites:");
  printf("State upstream and downstream range\n");
}




