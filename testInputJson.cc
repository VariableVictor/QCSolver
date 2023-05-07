#include <jansson.h>
#include <vector>


int main(int argc, char *argv[])
{
  json_t *pRoot;
  pRoot = json_load_file("./test.json", JSON_DECODE_ANY, NULL);
  if (0 == json_is_array(pRoot))
  {
    printf("file is not array");
    return 1;
  }
  int iSize = json_array_size(pRoot);
  printf("file is a array with %d elements.\n", iSize);

  json_t *pSize = json_array_get(pRoot, 0);//获得地图尺寸
  if (NULL == pSize)
  {
    printf("Can't get the size of map");
    return 1;
  }
  if (0 == json_is_array(pSize))
  {
    printf("size is not a array");
    return 1;
  }
  json_int_t jiSizey, jiSizex;

  jiSizey = json_integer_value(json_array_get(pSize,0));
  jiSizex = json_integer_value(json_array_get(pSize,1));
  printf("It's a %" JSON_INTEGER_FORMAT " x %" JSON_INTEGER_FORMAT " size map\n", jiSizey, jiSizex);

  for (int i = 1; i < iSize; i++)
  {
    json_t *pRC = json_array_get(pRoot, i);
    bool bH = (json_true() == json_array_get(pRC, 0));
    int irc = json_integer_value(json_array_get(pRC, 1));
    int iy = json_integer_value(json_array_get(pRC, 2));
    int ix = json_integer_value(json_array_get(pRC, 3));
    if (bH)
    {
      printf("this RC is a Horizon RC\n");
    }
    else
    {
      printf("this RC is not a Horizon RC\n");
    }
    printf("%d,%d,%d\n",irc,iy,ix);
  }
}
