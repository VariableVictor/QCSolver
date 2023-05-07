#include <string.h>
#include <jansson.h>

struct myRT
{
  bool bHo;
  int iS;
  int iY;
  int iX;
}leRTs[] =
{
  {true, 2, 2, 0},
  {true, 3, 0, 1},
  {true, 2, 1, 3},
  {true, 3, 5, 2},
  {false, 2, 1, 3},
  {false, 3, 3, 2},
  {false, 3, 5, 1}
};
//{
//  [0]{true, 2, 2, 0},
//  [1]{true, 3, 0, 1},
//  [2]{true, 2, 1, 3},
//  [3]{true, 3, 5, 2},
//  [4]{false, 2, 1, 3},
//  [5]{false, 3, 3, 2},
//  [6]{false, 3, 5, 1}
//};

json_t *myJson_RT(bool bHorizon, int iRTSize, int iRTy, int iRTx)
{
  json_t *pEleRT, *pBH;
  pEleRT = json_array();
  if (NULL == pEleRT)
    return NULL;
  if (bHorizon)
    pBH = json_true();
  else
    pBH = json_false();

  if (0 != json_array_append(pEleRT,pBH))
  {
    printf("err 6,1\n");
    return NULL;
  }
  if (0 != json_array_append(pEleRT,json_integer(iRTSize)))
  {
    printf("err 6,2\n");
    return NULL;
  }
  if (0 != json_array_append(pEleRT,json_integer(iRTy)))
  {
    printf("err 6,3\n");
    return NULL;
  }
  if (0 != json_array_append(pEleRT,json_integer(iRTx)))
  {
    printf("err 6,4\n");
    return NULL;
  }
  return pEleRT;
}
int main(int argc, char *argv[])
{
  json_t *pRoot, *pSize, *pRc;
  pRoot = json_array();
  if (NULL == pRoot)
  {
    printf("err 1\n");
    return 1;
  }
  pSize = json_array();
  if (NULL == pSize)
  {
    printf("err 2\n");
    return 2;
  }

  if (0 != json_array_append(pSize, json_integer(6)))
  {
    printf("err 3\n");
    return 3;
  }
  if (0 != json_array_append(pSize, json_integer(6)))
  {
    printf("err 4\n");
    return 4;
  }
  if (0 != json_array_append(pRoot, pSize))
  {
    printf("err 5\n");
    return 5;
  }
  for (int i = 0; i < 7; i++)
  {
    pRc = myJson_RT(leRTs[i].bHo, leRTs[i].iS, leRTs[i].iY, leRTs[i].iX);
    if (NULL == pRc)
    {
      printf("err 6,%d\n", i);
      return 6;
    }
    if (0 != json_array_append(pRoot, pRc))
    {
      printf("err 7\n");
      return 7;
    }
  }
  if (0 != json_dump_file(pRoot, "./test.json", JSON_ENCODE_ANY))
  {
    printf("err 100\n");
    return 100;
  }
}
