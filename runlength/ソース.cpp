#include <iostream>
#include <vector>
#include "func.h"

int main()
{
	std::vector<node_t> list;
	node_t buffer;
	buffer.letter_counter = 0;
	buffer.letter[127];
	for (int i = 0; i < (sizeof(buffer.letter) / sizeof(buffer.letter[0])); i++) {
		buffer.letter[i] = '\0';
	}
	//圧縮前の文字列
	unsigned const char uncompressed_word[] = "478194792758925892758973587787535353333355254526";
	//文字列のインデックス
	int word_index = 0;
	//ひとつ前の文字と今の文字が連続していたか
	bool continuous = false;
	printf("word = %s\n", uncompressed_word);
	while (uncompressed_word[word_index] != '\0') {
		char current_letter = uncompressed_word[word_index];
		char next_letter = uncompressed_word[word_index + 1];
		//printf("current = %c　", current_letter);
		//printf("next = %c　", next_letter);
		if (current_letter == next_letter) {
			
			if (continuous) {
				increase_counter_buf(&buffer);
			}
			else {
				if (buffer.letter[0] != '\0') {
					list.push_back(buffer);
					init_buf(&buffer);
				}
				add_letter_buf(&buffer, current_letter);
				increase_counter_buf(&buffer);
			}
			continuous = true;
		}
		else {
			if (continuous) {
				increase_counter_buf(&buffer);
				list.push_back(buffer);
				init_buf(&buffer);
			}
			else {
				add_letter_buf(&buffer, current_letter);
				increase_counter_buf(&buffer);
			}
			continuous = false;
		}
		view_buf(&buffer);
		printf("count = %d\n",word_index);
		word_index++;
	}
	if (buffer.letter[0] != '\0') list.push_back(buffer);

	//圧縮後
	printf("リスト\n");
	for (auto a : list) {
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			printf("%c", a.letter[i]);
		}
		printf(" %d個", a.letter_counter);
		printf("\n");
	}
}