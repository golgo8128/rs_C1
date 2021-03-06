#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
static char upto; /* 上流何塩基まで表示するかを指定 */
static char down; /* 下流何塩基まで表示するかを指定 */
/* パラメータ処理 */
int trsite2_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-trsite2") == 0){
    upto = atoi(argv[n + 1]); 
    /* ２番目のパラメータを上流で表示する塩基数とする */
    down = atoi(argv[n + 2]);
    /* ３番目のパラメータを下流で表示する塩基数とする */
    return 3; /* パラメータが２つ */
  }
  else return 0;
}
void trsite2_head(char *line){
}
/* エントリ処理 */
void trsite2_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i, j, begin, end, k, dobe, doen;
  printf("%s", entry_info->entry_line); 
  for(i = 0;i < ncds;i ++){ /* コード領域の数だけ処理を繰り返す(始) */
    if(cds[i].complement == 0 && cds[i].cds_start != 0){
      /* コード領域が二重鎖の反対側でなく、翻訳開始領域が明確(始) */
      begin = cds[i].cds_start - upto; /* 上流の表示開始地点 */
      end = cds[i].cds_start + 2;      /* 開始コドンの最後の塩基 */
      for(j = begin;j <= end;j ++){ /* 塩基を上流から開始コドンまで表示 */
	if(j >= 1 && j <= max)putchar(seqn[j-1]);
	else putchar(' '); /* データがないときは、空白を表示 */
      }
      putchar('\n');
      dobe = cds[i].cds_start + 1; /* 下流の表示開始地点 */
      doen = cds[i].cds_start + down; /* 下流の表示最終地点 */
      for(k = dobe; k <= doen; k++){ /* 塩基を下流の始めから終わりまで表示 */
	if(k >= 1 && k<= max)putchar(seqn[k+1]);
	else putchar(' ');
      }
      putchar('\n');
    } /* コード領域が二重鎖の反対側でなく、翻訳開始領域が明確(終) */
  } /* コード領域の数だけ処理を繰り返す(終) */
}
/* 最終処理 */
void trsite2_fin(){
  printf("Finished!!\n");
}
/* ヘルプ */
void trsite2_help(){
  printf("-trsite2\t Displays sequences around translation initiation sites\n");
}




