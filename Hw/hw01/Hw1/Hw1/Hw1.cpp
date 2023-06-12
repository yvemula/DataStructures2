#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
void flush_left(ofstream& output, string& line, const std::string empty, int& len) {
	output << line << endl;
	line = empty;
	len = 0;
}
void flush_right(int& starting_index, // reference to the starting index for placing words within the current line
	const int text_width, // width of the text
	int& text_length, // reference to the length of the text
	int& is_full, // flag for determining whether the text is full
	std::vector<std::string>& words_on_line, // vector of strings representing words on the current line
	std::ofstream& output_file, // output file stream
	std::string& current_line, // reference to the current line of text
	const std::string empty_line) // constant string representing an empty line
{
	// calculate the number of spaces to add to the line to achieve the desired width
	int add_spaces = text_width - text_length;
	// adjust the starting index accordingly
	starting_index += add_spaces;
	int line_length = text_length;
	bool is_star = false;
	int index = 0;
	// check if the text is not full and have a length less than the width
	if (text_length <= text_width && is_full == 0) {
		starting_index++;
		is_star = true;
	}
	if (is_star)
		is_full = 0;
	// loop through the words in the vector, placing each one in the current line at the updated starting index
	for (std::string word : words_on_line) {
		current_line.replace(starting_index, word.size(), word);
		starting_index += word.size();
		// add spaces between words
		if (index < words_on_line.size() - 1) {
			starting_index++;
		}
		index++;
	}
	// reset the starting index 
	starting_index = 2;
	// clear the vector of words
	words_on_line.clear();
	// call flush_left function to flush the current line to the output file and reset the line to an empty state
	flush_left(output_file, current_line, empty_line, text_length);
}

void full_justify(int& is_full, int& text_length, std::vector<std::string>& words, const int max_width, std::string& current_line, int& current_pos, std::ofstream& output, const std::string empty_line) {
	// calculate the number of spaces needed between words and the number of extra spaces to be distributed among the words
	int num_words = words.size();
	int spaces = (num_words == 1 || num_words == 2) ? max_width - text_length - 1 : (max_width - text_length) / (num_words - 1);
	int extra_spaces = (num_words == 1 || num_words == 2) ? 0 : (max_width - text_length) % (num_words - 1);

	// iterate through the words, replacing them in the current line and adjusting the current position accordingly
	for (int i = 0; i < num_words; i++) {
		current_line.replace(current_pos, words[i].size(), words[i]);
		current_pos += words[i].size();
		if (i < extra_spaces) {
			current_pos += spaces + 1;
		}
		else if (i < num_words - 1) {
			current_pos += spaces;
		}
	}

	// clear the words vector and flush left the current line to the output file
	if (is_full == 0) text_length -= 1;
	else is_full = 0;
	words.clear();
	flush_left(output, current_line, empty_line, text_length);
	// reset the current position
	current_pos = 2;
}


void process_str(const std::string& mode, std::ofstream& out_str, const std::vector<std::string>& input, int width, std::string& one_line, const std::string& empty_line) {
	int start_pos = 2, occupied_length = 0, i = 0, full = 0;
	std::vector<std::string> line_words;

	// Iterate through input words
	while (i < input.size()) {
		// Check if current word is longer than width
		if (input[i].size() > width) {
			// Flush current line if it is not empty
			if (occupied_length != 0) {
				if (mode == "flush_left") {
					flush_left(out_str, one_line, empty_line, occupied_length);
				}
				else if (mode == "flush_right") {
					flush_right(start_pos, width, occupied_length, full, line_words, out_str, one_line, empty_line);
				}
				else {
					full_justify(full, occupied_length, line_words, width, one_line, start_pos, out_str, empty_line);
				}
			}

			// Write long word in new lines
			int count = input[i].size() / (width - 1);
			int res = input[i].size() % (width - 1);
			for (int j = 0; j < count - 1; ++j) {
				one_line.replace(start_pos, width, input[i].substr(j * (width - 1), width - 1) + "-");
				flush_left(out_str, one_line, empty_line, occupied_length);
			}
			if (res == 1) {
				one_line.replace(start_pos, width, input[i].substr((count - 1) * (width - 1), width));
				flush_left(out_str, one_line, empty_line, occupied_length);
			}
			else {
				one_line.replace(start_pos, width, input[i].substr((count - 1) * (width - 1), width - 1) + "-");
				flush_left(out_str, one_line, empty_line, occupied_length);
				if (mode == "flush_left") {
					one_line.replace(start_pos, res, input[i].substr(count * (width - 1), res));
				}
				else {
					line_words.push_back(input[i].substr(count * (width - 1), res));
				}
				occupied_length = res;
				if (occupied_length < width) {
					occupied_length++;
				}
			}
		}
		else if (occupied_length + input[i].size() > width) {
			// Flush current line if it is full
			if (mode == "flush_left") {
				flush_left(out_str, one_line, empty_line, occupied_length);
			}
			else if (mode == "flush_right") {
				flush_right(start_pos, width, occupied_length, full, line_words, out_str, one_line, empty_line);
			}
			else {
				full_justify(full, occupied_length, line_words, width, one_line, start_pos, out_str, empty_line);
			}
			continue;
		}
		else {
			// Add word to current line
			if (mode == "flush_left") {
				one_line.replace(start_pos + occupied_length, input[i].size(), input[i]);
			}
			else {
				line_words.push_back(input[i]);
			}
			occupied_length += input[i].size();
			if (occupied_length < width) {
				occupied_length++;
			}
		}
		i++;
	}if (mode == "flush_left") {
		flush_left(out_str, one_line, empty_line, occupied_length);
	}
	else if (mode == "flush_right") {
		flush_right(start_pos, width, occupied_length, full, line_words, out_str, one_line, empty_line);
	}
	else {
		full_justify(full, occupied_length, line_words, width, one_line, start_pos, out_str, empty_line);
	}
}
				
			
int main(int argc, char* argv[]) {
	// Check number of arguments
	if (argc != 5) {
		std::cerr << "Error: Invalid number of arguments. 4 arguments are required." << std::endl;
		return 1;
	}
	// Open input and output files
	std::ifstream inputFile(argv[1]);
	if (!inputFile.good()) {
		std::cerr << "Error: Unable to open input file " << std::string(argv[1]) << " for reading." << std::endl;
		return 1;
	}
	std::ofstream outputFile(argv[2]);
	if (!outputFile.good()) {
		std::cerr << "Error: Unable to open output file " << std::string(argv[2]) << " for writing." << std::endl;
		return 1;
	}
	// Read input file into a vector of words
	std::string word;
	std::vector<std::string> inputWords;
	while (inputFile >> word) {
		inputWords.push_back(word);
	}
	// Get width and mode from command line arguments
	int width = std::atoi(argv[3]);
	std::string mode(argv[4]);
	// Create strings to help with output
	std::string dashLine(width + 4, '-');

	std::string blankLine(width + 2, ' ');

	std::string emptyLine = "|" + blankLine + "|";
	std::string oneLine = emptyLine;
	outputFile << dashLine << std::endl;
	// Process input in different mode using if-else condition
	if (mode == "flush_left" || mode == "flush_right" || mode == "full_justify") {
		process_str(mode, outputFile, inputWords, width, oneLine, emptyLine);
	}
	else {
		std::cerr << "Error: Invalid mode specified in command line." << std::endl;
		return 1;
	}
	outputFile << dashLine << std::endl;
	return 0;
}


