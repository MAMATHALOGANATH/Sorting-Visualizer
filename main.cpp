#include <windows.h>
#include <GL/glut.h>
#include <string>
#include <vector>
#include <chrono>
#include <vector>
#include <chrono>
//Global Variables
extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;
extern std::vector<float> arrayElements;
extern std::vector<bool> isSorted;
extern int numElements;
extern int sTime;
extern int comparisons;
extern void draw(int x, int y);
extern void generate();

void bubbleSort();
void selectionSort();
void insertionSort();
void quickSort(int l, int r);
void mergeSort(int l, int r);

int partition(int l, int r);
void swap(float* a, float* b);
void merge(int l, int m, int r);

// Global Variables
// ----------------------------------------------------------------------------
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
std::vector<float> arrayElements;
std::vector<bool> isSorted;
int numElements = 10;
int sTime = 50;
int comparisons = 0;

// Function Prototypes
// ----------------------------------------------------------------------------

void display();
void init();

void draw(int x, int y);
void generate();

void displayText(std::string textToDraw, int x, int y);
void displayTitle(std::string textToDraw, int x, int y);
void displayInfo();

void menuFunc(int id);
void createMenu();

void clear();


void swap(float* a, float* b) {
	float t = *a;
	*a = *b;
	*b = t;
}

void bubbleSort()
{
	bool swapped;
	for (int i = 0; i < numElements; i++)
	{
		swapped = false;
		for (int j = 0; j < numElements - i - 1; j++)
		{
			draw(j, j + 1);
			if (arrayElements[j] > arrayElements[j + 1])
			{
				swap(&arrayElements[j], &arrayElements[j + 1]);
				bool swapped = true;
				Sleep(sTime);
				draw(j, j + 1);
			}
			comparisons++;
		}
		isSorted[numElements - i - 1] = true;
		draw(-1, -1);
		if (swapped = false)
		{
			break;
		}
	}
}

void selectionSort()
{
	int i, j, min_index;
	for (i = 0; i < numElements - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < numElements; j++)
		{
			draw(min_index, j);
			if (arrayElements[j] < arrayElements[min_index])
			{
				min_index = j;
			}
			Sleep(sTime);
			comparisons++;
		}
		swap(&arrayElements[min_index], &arrayElements[i]);
		isSorted[i] = true;
		draw(-1, -1);
	}
	Sleep(sTime);
	isSorted[numElements - 1] = true;
	draw(-1, -1);
}

void insertionSort()
{
	int i, j, key;
	isSorted[0] = true;
	draw(-1, -1);
	for (i = 1; i < numElements; i++)
	{
		key = arrayElements[i];
		j = i - 1;
		Sleep(sTime);
		draw(i, j);
		comparisons++;
		while (j >= 0 && arrayElements[j] > key)
		{
			draw(j, j + 1);
			arrayElements[j + 1] = arrayElements[j];
			arrayElements[j] = key;
			Sleep(sTime);
			draw(j, j + 1);
			isSorted[i] = true;
			draw(-1, -1);
			j = j - 1;
			comparisons++;
		}
		isSorted[i] = true;
		draw(-1, -1);
	}
}

int partition(int l, int r)
{
	int pivot = arrayElements[r];
	comparisons++;
	int i = (l - 1);
	for (int j = l; j <= r - 1; j++)
	{
		draw(i, j);
		comparisons++;
		if (arrayElements[j] < pivot)
		{
			i++;
			swap(&arrayElements[i], &arrayElements[j]);
		}
		Sleep(sTime);
		draw(i, j);
	}
	draw(i + 1, r);
	swap(&arrayElements[i + 1], &arrayElements[r]);
	Sleep(sTime);
	draw(i + 1, r);
	return (i + 1);
}

void quickSort(int l, int r)
{
	if (l < r)
	{
		int p = partition(l, r);
		isSorted[p] = true;
		Sleep(sTime);
		draw(-1, 1);
		quickSort(l, p - 1);
		quickSort(p + 1, r);
	}
	else if (l == r) {
		isSorted[l] = true;
		draw(-1, -1);
	}
}

void merge(int l, int m, int r)
{
	int leftEnd = m - l + 1;
	int rightStart = r - m;
	std::vector<float> L(leftEnd), R(rightStart);

	for (int i = 0; i < leftEnd; i++)
		L[i] = arrayElements[l + i];
	for (int j = 0; j < rightStart; j++)
		R[j] = arrayElements[m + 1 + j];
	int i = 0, j = 0, k = l;

	while (i < leftEnd && j < rightStart)
	{
		if (L[i] <= R[j])
			arrayElements[k] = L[i++];
		else
			arrayElements[k] = R[j++];
		isSorted[k++] = true;
		comparisons++;
		Sleep(sTime);
		draw(-1, -1);
	}
	while (i < leftEnd) {
		arrayElements[k] = L[i++];
		isSorted[k++] = true;
		comparisons++;
		Sleep(sTime);
		draw(-1, -1);
	}
	while (j < rightStart) {
		arrayElements[k] = R[j++];
		isSorted[k++] = true;
		comparisons++;
		Sleep(sTime);
		draw(-1, -1);
	}
}

void mergeSort(int l, int r)
{
	if (l >= r) {
		return;
	}
	int m = l + (r - l) / 2;
	mergeSort(l, m);
	mergeSort(m + 1, r);
	merge(l, m, r);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sorting Algorithm Visualizer");
	init();
	glutDisplayFunc(display);
	createMenu();
	glutMainLoop();

	return 0;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	generate();
}

void displayText(std::string textToDraw, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < textToDraw.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textToDraw[i]);
}

void displayTitle(std::string textToDraw, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < textToDraw.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textToDraw[i]);
}

void displayInfo()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	std::string title = "Sorting Visualizer";
	displayTitle(title, SCREEN_WIDTH * .4, 0.85 * SCREEN_HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string info = "Values: " + std::to_string(numElements) + "    Delay: " + std::to_string(sTime) + " ms delay";
	displayText(info, 5, 0.97 * SCREEN_HEIGHT);
}

void displayTotalTime(int diff, std::string algorithm)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string info = "Sort Algorithm: " + algorithm + "    Comparisons: " + std::to_string(comparisons);
	displayText(info, 5, 0.93 * SCREEN_HEIGHT);
	std::string totalTime = "Total Time: " + std::to_string(diff) + " ms";
	displayText(totalTime, 5, .89 * SCREEN_HEIGHT);
	glFlush();
}

void draw(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	float quadSize = (SCREEN_WIDTH - 2 * (numElements + 1.0)) / numElements;
	for (int i = 0; i < numElements; i++)
	{
		if (i == x || i == y)
			glColor3f(1.0f, 0.0f, 0.0f);
		else if (isSorted[i])
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2f(2 + i * (2 + quadSize), 0);
		glVertex2f(2 + i * (2 + quadSize), arrayElements[i]);
		glVertex2f(2 + i * (2 + quadSize) + quadSize, arrayElements[i]);
		glVertex2f(2 + i * (2 + quadSize) + quadSize, 0);
		glEnd();
	}
	displayInfo();
	glFlush();
}

void generate()
{
	comparisons = 0;
	isSorted.clear();
	arrayElements.clear();
	srand(time(0));
	for (int i = 0; i < numElements; i++)
	{
		arrayElements.push_back(((float)rand() / RAND_MAX) * SCREEN_HEIGHT * 0.8);
		isSorted.push_back(false);
	}
	draw(-1, -1);
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(0);
	glEnd();
	glFlush();
}

void menuFunc(int id)
{
	switch (id)
	{
	case 11: numElements = 10; generate(); break;
	case 12: numElements = 20; generate(); break;
	case 13: numElements = 50; generate(); break;
	case 14: numElements = 100; generate(); break;
	case 15: numElements = 200; generate(); break;
	case 16: numElements = 1000; generate(); break;

	case 21: sTime = 10; draw(-1, -1); break;
	case 22: sTime = 20; draw(-1, -1); break;
	case 23: sTime = 50; draw(-1, -1); break;
	case 24: sTime = 100; draw(-1, -1); break;
	case 25: sTime = 500; draw(-1, -1); break;

	case 31: {
		auto start = std::chrono::system_clock::now();
		bubbleSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "BubbleSort");
	} break;
	case 32: {
		auto start = std::chrono::system_clock::now();
		mergeSort(0, numElements - 1);
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "MergeSort");
	} break;
	case 33: {
		auto start = std::chrono::system_clock::now();
		quickSort(0, numElements - 1);
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "QuickSort");
	} break;
	case 34: {
		auto start = std::chrono::system_clock::now();
		selectionSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "SelectionSort");
	} break;
	case 35: {
		auto start = std::chrono::system_clock::now();
		insertionSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "InsertionSort");
	} break;
	case 4:exit(0);
	}
}

void createMenu() {
	int s1 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("10 Numbers", 11);
	glutAddMenuEntry("20 Numbers", 12);
	glutAddMenuEntry("50 Numbers", 13);
	glutAddMenuEntry("100 Numbers", 14);
	glutAddMenuEntry("200 Numbers", 15);
	glutAddMenuEntry("1000 Numbers", 16);

	int s2 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("10", 21);
	glutAddMenuEntry("20", 22);
	glutAddMenuEntry("50", 23);
	glutAddMenuEntry("100", 24);
	glutAddMenuEntry("500", 25);

	int s3 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("Bubble Sort", 31);
	glutAddMenuEntry("Merge Sort", 32);
	glutAddMenuEntry("Quick Sort", 33);
	glutAddMenuEntry("Selection Sort", 34);
	glutAddMenuEntry("Insertion Sort", 35);

	glutCreateMenu(menuFunc);
	glutAddSubMenu("Values", s1);
	glutAddSubMenu("Speed", s2);
	glutAddSubMenu("Sort", s3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}