#include<iostream>
#include<vector>
#include<iomanip>
const int MAX_START = 50;   // maximum starting number

using namespace std;


/**************************************************/
/*Function to allocate numbers in the spiral form
 * Pass the size of the array , which should be odd
 *and the starting middle value
 */
void do_prime_spiral(const int n, const int start);

/*Function to print the output in the spiral format,
 * in the anticlockwise direction
 *Pass the array and the size of the array
 */
void print_array (vector<vector<char>>,int N);
vector<int> generate_prime (int n, int start);
/**************************************************/

int main()
{
    do_prime_spiral(5, 1);
    do_prime_spiral(25, 11);
    do_prime_spiral(35, 0);
    do_prime_spiral(50, 31);
    do_prime_spiral(101, 41);
    return 0;
}


/***************************************************/
vector<int> generate_prime (int n, int start)
{
	vector<int> arr(n*n + start +2);
	arr[0] = 0;
	arr[1] = 0;
	for (int i = 2; i < (n*n + start + 2); i++)
		{
			arr[i] = i;
		}

	for(int i =2; i< (n*n + start +2); i++ )
	{
		if(arr[i] != 0)
		{
		  int j = 2;
		  while(arr[i]*j < (n*n + start +2) )
		  {
			  arr[i*j] = 0;
			  j++;
		  }
		}
	}

	vector<int> prime(n*n + start - 1);
	int j = 0;
	for (int i = start; i < (n*n + start) ; i++)
	{
		prime[j] = arr[i];
		j++;
	}
	return prime;
}
/**************************************************/
void do_prime_spiral(const int n, const int start)
{
	if (start >  MAX_START)
	{
		cout << "***** Error: Start value " << start << " must be lesser\n\n";
		return;
	}
	vector<int> prime;
	prime = generate_prime(n, start);

	vector<vector<char>> spiral(n);
	for (int i =0; i < n; i++)
	{
		spiral[i] = vector<char>(n);
		for(int j = 0; j < n; j++)
		{
			spiral[i][j] = '.';
		}
	}

	cout << "Prime Spiral of size "<< n << " starting at " << start<<endl;
	if ((start <= 0) || (start > 50))
	{
		cout << "***** Error: Starting value " << start << " < 1 or > 50\n\n";
		return;
	}
	if (n % 2 != 0)
	{
		int i(0), j(0), k(0);
		int s = 0;
		i = n/2;
		j = n/2;
		spiral[i][j] = (prime[s++] != 0 ) ? '#' : '.';
		for (k = 0; k < n/2; k++)
		{
			i = (n/2)+k;
			j = (n/2) + 1 + k;

			spiral[i][j] = (prime[s++] != 0 ) ? '#' : '.';
			while (--i >= ((n/2) - k - 1) )
			{
				spiral[i][j] = (prime[s++] != 0 ) ? '#' : '.';
			}

			i = (n/2) - k - 1;
			while (--j >= ((n/2) - k - 1))
			{
				spiral[i][j] = (prime[s++] != 0 ) ? '#' : '.';
			}

			j = (n/2) - k - 1;
			while (++i <= (n/2+1+k) )
			{
				spiral[i][j] = (prime[s++] != 0 ) ? '#' : '.';
			}

			i = n/2 + k + 1;
			while (++j <= (n/2+k+1))
			{
				spiral[i][j] =(prime[s++] != 0 ) ? '#' : '.';
			}

		}
		print_array(spiral,n);
	}
	else
	{
		cout << "***** Error: Size " << n << " must be odd.\n";
	}
	cout << endl;

}

/**************************************************************/
void print_array (vector<vector<char>> arr,int N)
{
	cout << endl;
	for (int i =0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
	return;
}

/**************************************************************/
