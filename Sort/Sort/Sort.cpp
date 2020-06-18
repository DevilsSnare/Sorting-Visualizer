#include <SDL.h>
#include <iostream>
#include <string>
#include <time.h>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool iscomplete = false;

const int arrsize = 128;
const int rectsize = 8;

int arr[arrsize];
int xarr[arrsize];

void visualize(int x = 0, int y = 0, int z = 0)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	int i = 0;
	for (int j = 0; j <= SCREEN_WIDTH - rectsize; j += rectsize)
	{
		SDL_PumpEvents();
		SDL_Rect rect = { j, 0, rectsize, arr[i] };
		if (iscomplete)
		{
			SDL_SetRenderDrawColor(renderer, 0, 204, 0, 0);
			SDL_RenderDrawRect(renderer, &rect);
		}
		else if (i == x || i == z)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(renderer, &rect);
		}
		else if (i == y)
		{
			SDL_SetRenderDrawColor(renderer, 102, 255, 102, 0);
			SDL_RenderFillRect(renderer, &rect);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderDrawRect(renderer, &rect);
		}
		i++;
	}
	SDL_RenderPresent(renderer);
}
void bubblesort()
{
	for (int i = 0;i < arrsize - 1;i++)
	{
		for (int j = 0;j < arrsize - 1 - i;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				visualize(j + 1, j, arrsize - 1);
			}
			SDL_Delay(2);
		}
	}
}
void insertionsort()
{
	for (int i = 1; i < arrsize; i++)
	{
		int j = i - 1;
		int temp = arr[i];
		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j--;
			visualize(i, j + 1);
			SDL_Delay(2);
		}
		arr[j + 1] = temp;
	}
}
void selectionsort()
{
	int min;
	for (int i = 0;i < arrsize - 1;i++)
	{
		min = i;
		for (int j = i + 1;j < arrsize;j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
				visualize(i, min);
			}
			SDL_Delay(2);
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
int partitionarray(int a[], int b, int c)
{
	int count_small = 0;

	for (int i = (b + 1);i <= c;i++)
	{
		if (a[i] <= a[b])
		{
			count_small++;
		}
	}
	int d = b + count_small;
	int temp = a[d];
	a[d] = a[b];
	a[b] = temp;
	visualize(d, b);

	int i = b, j = c;

	while (i<d && j>d)
	{
		if (a[i] <= a[d])
		{
			i++;
		}
		else if (a[j] > a[d])
		{
			j--;
		}
		else
		{
			int temp_1 = a[j];
			a[j] = a[i];
			a[i] = temp_1;

			visualize(i, j);
			SDL_Delay(2);

			i++;
			j--;
		}
	}
	return d;
}
void quicksort(int a[], int b, int c)
{
	if (b >= c)
	{
		return;
	}
	int d = partitionarray(a, b, c);
	quicksort(a, b, d - 1);
	quicksort(a, d + 1, c);
}
void xmergesort(int a[], int b, int c)
{
	int size = (c - b) + 1;
	vector<int> output(size);
	int mid = (b + c) / 2;
	int i = b, j = mid + 1, k = 0;
	while (i <= mid && j <= c)
	{
		if (a[i] <= a[j])
		{
			output[k] = a[i];
			visualize(i, j);
			i++;
			k++;
		}
		else
		{
			output[k] = a[j];
			visualize(i, j);
			j++;
			k++;
		}

	}
	while (i <= mid)
	{
		output[k] = a[i];
		visualize(-1, i);
		i++;
		k++;
	}
	while (j <= c)
	{
		output[k] = a[j];
		visualize(-1, j);
		j++;
		k++;
	}
	int x = 0;
	for (int l = b; l <= c; l++)
	{
		a[l] = output[x];
		visualize(l);
		SDL_Delay(2);
		x++;
	}
}
void mergesort(int a[], int b, int c)
{
	if (b >= c)
	{
		return;
	}
	int mid = (b + c) / 2;
	mergesort(a, b, mid);
	mergesort(a, mid + 1, c);
	xmergesort(a, b, c);
}
void heapsort(int* input, int n)
{
	for (int i = 1; i < n; i++)
	{
		int childIndex = i;
		int parentIndex = (childIndex - 1) / 2;

		while (childIndex > 0)
		{
			if (input[childIndex] < input[parentIndex])
			{
				int temp = input[parentIndex];
				input[parentIndex] = input[childIndex];
				input[childIndex] = temp;

			}
			else
			{
				break;
			}

			visualize(parentIndex, childIndex);
			SDL_Delay(2);

			childIndex = parentIndex;
			parentIndex = (childIndex - 1) / 2;
		}
	}

	for (int heapLast = n - 1; heapLast >= 0; heapLast--)
	{
		int temp = input[0];
		input[0] = input[heapLast];
		input[heapLast] = temp;

		int parentIndex = 0;
		int leftChildIndex = 2 * parentIndex + 1;
		int rightChildIndex = 2 * parentIndex + 2;

		while (leftChildIndex < heapLast)
		{
			int minIndex = parentIndex;

			if (input[leftChildIndex] < input[minIndex])
			{
				minIndex = leftChildIndex;
			}
			if (rightChildIndex < heapLast && input[rightChildIndex] < input[minIndex])
			{
				minIndex = rightChildIndex;
			}
			if (minIndex == parentIndex)
			{
				break;
			}

			int temp = input[parentIndex];
			input[parentIndex] = input[minIndex];
			input[minIndex] = temp;

			visualize(minIndex, parentIndex, heapLast);
			SDL_Delay(2);

			parentIndex = minIndex;
			leftChildIndex = 2 * parentIndex + 1;
			rightChildIndex = 2 * parentIndex + 2;
		}
	}
}
void load()
{
	memcpy(arr, xarr, sizeof(int) * arrsize);
}
void generaterandomarray()
{
	long long int seed = (long long)time(NULL);
	srand(seed);
	for (int i = 0;i < arrsize;i++)
	{
		int temp = rand() % (SCREEN_HEIGHT);
		xarr[i] = temp;
	}
}
bool sdl()
{
	bool issuccuess = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initialized.\n";
		cout << "SDL Error: " << SDL_GetError();
		issuccuess = false;
	}
	else
	{
		window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	return issuccuess;
}
void program()
{
	if (!sdl())
	{
		cout << "SDL Initialization Failed\n";
	}
	else
	{
		generaterandomarray();
		load();
		SDL_Event event;
		bool isquit = false;
		while (!isquit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					isquit = true;
					iscomplete = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case(SDLK_q):
						isquit = true;
						iscomplete = false;
						cout << "\nExiting\n";
						break;
					case(SDLK_n):
						generaterandomarray();
						iscomplete = false;
						load();
						cout << "\nRandom array generated\n";
						break;
					case(SDLK_1):
					{
						load();
						iscomplete = false;
						clock_t start;
						double duration;
						start = clock();
						cout << "\nBubble Sort started\n";
						bubblesort();
						iscomplete = true;
						cout << "\nBubble Sort successfully completed\n";
						duration = (clock() - (double)start) / (double)CLOCKS_PER_SEC;
						cout << "Time Taken: " << duration << " seconds\n";
						break;
					}
					case(SDLK_2):
					{
						load();
						iscomplete = false;
						clock_t start;
						double duration;
						start = clock();
						cout << "\nInsertion Sort started\n";
						insertionsort();
						iscomplete = true;
						cout << "\nInsertion Sort successfully completed\n";
						duration = (clock() - (double)start) / (double)CLOCKS_PER_SEC;
						cout << "Time Taken: " << duration << " seconds\n";
						break;
					}
					case(SDLK_3):
					{
						load();
						iscomplete = false;
						clock_t start;
						double duration;
						start = clock();
						cout << "\nSelection Sort started\n";
						selectionsort();
						iscomplete = true;
						cout << "\nSelection Sort successfully completed\n";
						duration = (clock() - (double)start) / (double)CLOCKS_PER_SEC;
						cout << "Time Taken: " << duration << " seconds\n";
						break;
					}
					case(SDLK_4):
					{
						load();
						iscomplete = false;
						clock_t start;
						double duration;
						start = clock();
						cout << "\nQuick Sort started\n";
						quicksort(arr, 0, arrsize - 1);
						iscomplete = true;
						cout << "\nQuick Sort successfully completed\n";
						duration = (clock() - (double)start) / (double)CLOCKS_PER_SEC;
						cout << "Time Taken: " << duration << " seconds\n";
						break;
					}
					case(SDLK_5):
					{
						load();
						iscomplete = false;
						clock_t start;
						double duration;
						start = clock();
						cout << "\nMerge Sort started\n";
						mergesort(arr, 0, arrsize - 1);
						iscomplete = true;
						cout << "\nMerge Sort successfully completed\n";
						duration = (clock() - (double)start) / (double)CLOCKS_PER_SEC;
						cout << "Time Taken: " << duration << " seconds\n";
						break;
					}
					case(SDLK_6):
					{
						load();
						iscomplete = false;
						clock_t start;
						double duration;
						start = clock();
						cout << "\nHeap Sort started\n";
						heapsort(arr, arrsize);
						iscomplete = true;
						cout << "\nHeap Sort successfully completed\n";
						duration = (clock() - (double)start) / (double)CLOCKS_PER_SEC;
						cout << "Time Taken: " << duration << " seconds\n";
						break;
					}
					case(SDLK_x):
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						SDL_DestroyWindow(window);
						window = NULL;
						SDL_Quit();
						return;
					}
				}
			}
			visualize();
		}
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_Quit();
	}
}
void start1()
{
	cout << "\n";
	cout << "      ----SORTING VISUALIZER----\n";
	cout << "   ________________________________\n";
	cout << "Written in C++ using the SDL2 library\n";
	cout << "                  -                   \n";
	cout << "\n     **Press Enter to continue**\n";
	string command;
	getline(cin, command);
	if (command == "\n")
	{
		return;
	}
}
void start2()
{
	cout << "   ________________________________\n";
	cout << "\nPlease follow the instructions given below:\n";
	cout << "Press N to generate random array of numbers\n";
	cout << "Press 1 to sort using BUBBLE SORT algorithm\n";
	cout << "Press 2 to sort using INSERTION SORT algorithm\n";
	cout << "Press 3 to sort using SELECTION SORT algorithm\n";
	cout << "Press 4 to sort using QUICK SORT algorithm\n";
	cout << "Press 5 to sort using MERGE SORT algorithm\n";
	cout << "Press 6 to sort using HEAP SORT algorithm\n";
	cout << "Press X to exit\n";
	cout << "   ________________________________\n";
	cout << "\nNOTE: Give one command at a time.\n";
	cout << "\n     **Press Enter to continue**\n";
	string command;
	getline(cin, command);
	if (command == "\n")
	{
		return;
	}
}
int main(int argc, char* args[])
{
	start1();
	start2();
	program();
	clock_t start_time = clock();
	while (clock() < start_time + 1000)
		;

	return 0;
}