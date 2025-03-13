#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

// Helper function to check if two words are adjacent
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// Check if two words have an edit distance of at most d
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false; // Length difference is too large

    int i = 0, j = 0, edits = 0;
    
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            edits++;
            if (edits > d) return false;
            if (len1 > len2) i++; // Deletion in str1
            else if (len1 < len2) j++; // Insertion in str1
            else { i++; j++; } // Substitution
        } else {
            i++;
            j++;
        }
    }
    
    return edits + (len1 - i) + (len2 - j) <= d;
}

// Load dictionary words from file
void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

// Generate the shortest word ladder using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited.insert(word);

                if (word == end_word) {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    }

    return {}; // Return empty vector if no ladder is found
}

// Print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

// Verify user input and run word ladder search
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words must be different");
    }

    if (word_list.find(end_word) == word_list.end()) {
        error(start_word, end_word, "End word is not in the dictionary");
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
}
