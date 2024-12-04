#include <iostream>
#include <fstream>
#define MAX_LEN 60

using namespace std;

void push(char *line, int size, int position) {
    for (int i=size-1; i>= position; i--) {
        line[i+1] = line[i];
    }
    line[position] = ' ';
}

void pad(char *line, int size) {
    int index = size - 1;

    while (size != MAX_LEN) {
        if (line[index] == ' ' and line[index-1] != ' ') {
            push(line, size, index);
            size += 1;
        }
        
        if (index > 0) {
            index = index - 1;
        } else {
            index = size - 1;
        }
    }
}

void print(char *line, int size, bool pad_line) {
    if (pad_line) {
        pad(line, size);
        size = MAX_LEN;
    }

    for (int i=0; i<size; i++) {
        cout << line[i];
    }
    cout << endl;
}


int read_word(ifstream &file, char *word) {
    int len = 0;
    while (true) {
        char c = file.get();
        if (c == EOF) {
            return -1;
        }
        
        if (c == ' ' || c == '\n') {
            break;
        }

        word[len] = c;
        len += 1;
    }
    return len;

}

bool can_fit(char *line, int line_size, char *word, int word_size) {
    return (line_size + 1 + word_size <= MAX_LEN);
}


int append(char *line, int line_size, char *word, int word_size) {
    if (line_size > 0) {
        line[line_size] = ' ';
        line_size += 1;
    }

    for (int i=0; i < word_size; i++) {
        line[line_size] = word[i];
        line_size += 1;
    }

    return line_size;

}



int main() {
    ifstream file("text.txt");
 
    char word[20];
    int word_size;

    char line[MAX_LEN];
    int line_size;

    while (true) {
        word_size = read_word(file, word);

        if (word_size < 0) {
            break;
        }

        if (word_size == 0) {
            continue;
        }

        if (can_fit(line, line_size, word, word_size)) {
            line_size = append(line, line_size, word, word_size);
        } else {
            print(line, line_size, true);
            line_size = 0;
            line_size = append(line, line_size, word, word_size);
        }


    }
    
    print(line, line_size, false);


}