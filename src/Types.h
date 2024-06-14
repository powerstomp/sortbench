#include <cstring>

static const char *SORTS[] = {
	"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort",
	"shell-sort", "heap-sort", "merge-sort", "quick-sort",
	"counting-sort", "radix-sort", "flash-sort"
};
static const int SORT_COUNT = sizeof(SORTS) / sizeof(SORTS[0]);
enum SortType {
	Selection, Insertion, Bubble, Shaker,
	Shell, Heap, Merge, Quick,
	Counting, Radix, Flash
};
static const char *SORT_NAMES[] = {
    "Selection Sort", "Insertion Sort", "Bubble Sort", "Shaker Sort",
    "Shell Sort", "Heap Sort", "Merge Sort", "Quick Sort",
    "Counting Sort", "Radix Sort", "Flash Sort"
};

static const char *INPUT_ORDERS[] = {
	"-rand", "-nsorted", "-sorted", "-rev"
};
static const int INPUT_ORDER_COUNT =
	sizeof(INPUT_ORDERS) / sizeof(INPUT_ORDERS[0]);
enum InputOrder {
	Random, NearlySorted, Sorted, ReverseSorted
};
static const char *INPUT_ORDER_NAMES[] = {
	"Random", "Nearly Sorted", "Sorted", "Reverse Sorted"
};

static const char *OUTPUT_TYPES[] = {
	"", "-time", "-comp", "-both"
};
static const int OUTPUT_TYPE_COUNT =
	sizeof(OUTPUT_TYPES) / sizeof(OUTPUT_TYPES[0]);
enum OutputType {
	Time = 0b01, Comparisons = 0b10, Both = 0b11
};

inline int ParseOption(const char *str, const char *options[], int n) {
	for (int i = 0; i < n; i++)
		if (strcmp(str, options[i]) == 0)
			return i;
	return -1;
}
