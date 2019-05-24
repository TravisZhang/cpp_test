#include <bits/stdc++.h>

using namespace std;

// typedef vector<vector<int> vector<vector<int>;

class Mypair
{
  public:
    int a = 0;
    int b = 0;

    Mypair(int x, int y){a = x;b = y;}
};

vector<vector<vector<int>>> generate_all(void);

// Complete the formingMagicSquare function below.
int formingMagicSquare(vector<vector<int>> s) {
  int min_cost = 500;
  vector<vector<vector<int>>> result = generate_all();
  int size = result.size();
  printf("result size: %d\n",size);
  for(int i = 0;i < size;++i)
  {
    vector<vector<int>> s_temp = result[i];
    int cost_temp = 0;
    for(int j = 0;j < 3;++j)
    {
      for(int k = 0;k < 3;++k)
      {
        cost_temp += abs(s_temp[j][k]-s[j][k]);
      }
      
    }
    if(cost_temp < min_cost)
    {
      min_cost = cost_temp;
    }
  }

  return min_cost;

}

vector<vector<vector<int>>> generate_all(void){
  vector<vector<vector<int>>> result;
  vector<vector<int>> s(3);
  vector<Mypair> pair_list;
  vector<int> status;
  for(int i = 0;i < 3;++i)
  {
    Mypair pair1(0,i);
    pair_list.push_back(pair1);
  }
  for(int i = 0;i < 3;++i)
  {
    if(i == 0||i == 2) continue;
    Mypair pair2(i,0);
    pair_list.push_back(pair2);
  }
  printf("pair_list size: %ld\n",pair_list.size());
  
  for(int i = 0;i < 4;++i)
  {
    for(int m = 0; m < 3;++m) {
      s[m].resize(3,0);
    }
    s[1][1] = 5;
    status.resize(4,0);

    status[i] = 1;
    for(int i0 = 0;i0 < 2;++i0)
    {
      if(i0 == 0) 
      {
        s[pair_list[i].a][pair_list[i].b] = 1;
        s[2-pair_list[i].a][2-pair_list[i].b] = 9;
      }
      else 
      {
        s[pair_list[i].a][pair_list[i].b] = 9;
        s[2-pair_list[i].a][2-pair_list[i].b] = 1;
      }
      
      for(int j = 0;j < 4;++j)
      {
        if(status[j] == 1) continue;
        status[j] = 1;
        for(int j0 = 0;j0 < 2;++j0)
        {
          if(j0 == 0) 
          {
            s[pair_list[j].a][pair_list[j].b] = 2;
            s[2-pair_list[j].a][2-pair_list[j].b] = 8;
          }
          else 
          {
            s[pair_list[j].a][pair_list[j].b] = 8;
            s[2-pair_list[j].a][2-pair_list[j].b] = 2;
          }

          for(int k = 0;k < 4;++k)
          {
            if(status[k] == 1) continue;
            status[k] = 1;
            for(int k0 = 0;k0 < 2;++k0)
            {
              if(k0 == 0) 
              {
                s[pair_list[k].a][pair_list[k].b] = 3;
                s[2-pair_list[k].a][2-pair_list[k].b] = 7;
              }
              else 
              {
                s[pair_list[k].a][pair_list[k].b] = 7;
                s[2-pair_list[k].a][2-pair_list[k].b] = 3;
              }

              for(int l = 0;l < 4;++l)
              {
                if(status[l] == 1) continue;
                status[l] = 1;
                for(int l0 = 0;l0 < 2;++l0)
                {
                  if(l0 == 0) 
                  {
                    s[pair_list[l].a][pair_list[l].b] = 4;
                    s[2-pair_list[l].a][2-pair_list[l].b] = 6;
                  }
                  else 
                  {
                    s[pair_list[l].a][pair_list[l].b] = 6;
                    s[2-pair_list[l].a][2-pair_list[l].b] = 4;
                  }

                  result.push_back(s);
                }
                status[l] = 1;
              }
            }
            status[k] = 0;
          } 
        }
        status[j] = 0;
      }
    }
    status[i] = 0;
  }

  return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);
    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> s[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = formingMagicSquare(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
