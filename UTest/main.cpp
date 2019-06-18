#include "main.h"

static const int
	V_SIZE = 10,
	RAND_ORDER = (V_SIZE * 1000000); //for numbers < 1000

String
	unsorted = "ibgehacfdj",
	expected_sorted = "abcdefghij",
	one_char_string = "aaaaaaaaaa",
	zeros_string = "\0\0\0\0\0\0\0\0\0\0",
	zeros_ones_string = "a\0a\0a\0a\0a\0",
	sorted_zeros_ones_string = "a";

inline void print_vector(String & data){
	String::iterator current = data.begin();
	String::iterator end = data.end() - 1;
	if(end - current < 0) return;

	std::cout << "Vector is: ";
	while(current <= end){
		std::cout << *current << " ";
		current++;
	}
	std::cout << std::endl;
}

TEST(sort_test, sort_random_unsorted){
	String raw = unsorted;
	qsort_recursive(raw);
	ASSERT_TRUE(raw == expected_sorted) << "vector not sorted!\n";
}

TEST(sort_test, sort_sorted){
	String raw = expected_sorted;
	qsort_recursive(raw);
	ASSERT_TRUE(raw == expected_sorted) << "vector not sorted!\n";
}

TEST(sort_test, sort_ones_vector){
	String raw = one_char_string;
	qsort_recursive(raw);
	ASSERT_TRUE(raw == one_char_string);
}

TEST(sort_test, sort_zeros_vector){
	String raw = zeros_string;
	qsort_recursive(raw);
	ASSERT_TRUE(raw == zeros_string);
}

TEST(sort_test, sort_zeros_ones_vector){
	String raw = zeros_ones_string;
	qsort_recursive(raw);
	ASSERT_TRUE(raw == sorted_zeros_ones_string);
}

TEST(file_test,file_write){
    String raw = unsorted;
    std::ifstream f;
    f.open(TEST_PATH, std::ios::in);
    ASSERT_TRUE( f.is_open() ) << "Cat open file" ;
   
}

TEST(file_test,file_read){
    String raw = expected_sorted;
    std::ofstream f;
    f.open(TEST_PATH, std::ios::out);
    ASSERT_TRUE(f.is_open()) << "Cat open file" ;
}
	   
TEST(main_test, sort_files){
	String raw = unsorted;
	std::ifstream f;
	f.open(TEST_PATH, std::ios::in);
	f>>raw;
	qsort_recursive(raw);
	ASSERT_TRUE(raw == expected_sorted);
}

int main(int argc, char ** argv)
{
	const size_t kFileSize = 40;
	int * input_data = new int[kFileSize];

    const char * input_path = TEST_PATH;
	ReadFile(input_path, input_data, kFileSize);

	try {
		qsort_recursive(input_data);
	}
	catch (const char * exception)
	{
		std::cerr << exception;
	}

	const char* output_path = TEST_PATH;
	WriteFile(output_path, input_data, kFileSize);

    delete[] input_data;

	try{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
	catch(const char * exception)
	{
		std::cerr << exception;
	}
}

void qsort_recursive(String & raw) {
	#ifdef DEBUG_FLAG
		const char * path_lib = "../src/sort_lib/Debug/sort_lib.dll";
	#else
		const char * path_lib = "../src/sort_lib/Release/sort_lib.dll";
	#endif

	HINSTANCE hinst_lib = LoadLibrary(path_lib);

	if (!hinst_lib){
		throw "Error: can't find sort_lib.dll\n";
	}

	static _qsort_reqursive DllFunc =
		(_qsort_reqursive)GetProcAddress(hinst_lib, "qsort_recursive");

	if (!DllFunc){
		throw "Error: can't find function\n";
	}
	else{
		DllFunc(left_edge, right_edge);
	}

	FreeLibrary(hinst_lib);
}