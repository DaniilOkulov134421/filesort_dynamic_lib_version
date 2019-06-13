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
	
	

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
