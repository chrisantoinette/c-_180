#include <vector>
#include "png.h"

using namespace std;

int main(int argc, char *argv[])
{
  vector<vector<int>> image = readGrayscaleImage("blimp.png");
   int j=6;
    //bool on = false;
    for(int i= 0; i< image.size(); i++)
    {
      while (j<image[0].size())
      {
        image[i][j] = 0;
    	  /*if(!on)
  		  {
    			j += 7;
    			on = true;
  		  }
		    else
  		  {*/
  			  j += 7;
  		  //}
      }
      j = (j % image[i].size());
    }
  writeGrayscaleImage("out.png", image);
}
