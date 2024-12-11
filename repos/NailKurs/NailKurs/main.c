#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>

// ������������� ��������� �������
void set_console_encoding() {
    SetConsoleCP(CP_UTF8);        // ��������� ����� UTF-8
    SetConsoleOutputCP(CP_UTF8); // ��������� ������ UTF-8
}

// ���������� ������ � ������� �������� (��� ������� ��������)
void to_lowercase_wchar(wchar_t* str) {
    for (wchar_t* p = str; *p; ++p) {
        *p = towlower(*p);
    }
}

wchar_t* convert_to_wchar(const char* str) {
    size_t len = strlen(str) + 1;
    wchar_t* wstr = (wchar_t*)malloc(len * sizeof(wchar_t)); // ����� ���������� � wchar_t*
    if (wstr) {
        mbstowcs(wstr, str, len);
    }
    return wstr;
}

// ������� ��������� ����� � �����
int count_word_in_file(const wchar_t* filename, const wchar_t* word) {
    FILE* file = _wfopen(filename, L"r, ccs=UTF-8");
    if (!file) {
        perror("������ ��� �������� �����");
        return -1;
    }

    int count = 0;
    wchar_t buffer[1024];
    wchar_t word_lower[1024];

    // �������� ������� ����� � ������� ��������
    wcscpy(word_lower, word);
    to_lowercase_wchar(word_lower);

    while (fgetws(buffer, sizeof(buffer) / sizeof(wchar_t), file)) {
        wchar_t* context = NULL;
        wchar_t* token = wcstok(buffer, L" \t\n.,!?\"'()", &context); // ������� context
        while (token) {
            wchar_t token_lower[1024];
            wcscpy(token_lower, token);
            to_lowercase_wchar(token_lower);

            if (wcscmp(token_lower, word_lower) == 0) {
                count++;
            }
            token = wcstok(NULL, L" \t\n.,!?\"'()", &context); // ���������� ��� �� context
        }
    }

    fclose(file);
    return count;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    set_console_encoding();

    if (argc != 3) {
        printf("�������������: ./c_finder <���� � ��������> <����� ��� ������>\n");
        return 1;
    }

    const char* directory_path = argv[1];
    const char* search_word_char = argv[2];
    wchar_t* search_word = convert_to_wchar(search_word_char);

    wchar_t search_path[MAX_PATH];
    WIN32_FIND_DATAW find_data;
    HANDLE h_find;

    swprintf(search_path, MAX_PATH, L"%hs\\*.txt", directory_path);

    h_find = FindFirstFileW(search_path, &find_data);
    if (h_find == INVALID_HANDLE_VALUE) {
        wprintf(L"��������� ����� �� ������� � ��������: %hs\n", directory_path);
        free(search_word);
        return 0;
    }

    do {
        wchar_t file_path_w[MAX_PATH];
        swprintf(file_path_w, MAX_PATH, L"%hs\\%ls", directory_path, find_data.cFileName);

        int count = count_word_in_file(file_path_w, search_word);
        if (count >= 0) {
            wprintf(L"��� �����: %ls, ������� ����: %d\n", find_data.cFileName, count);
        }
    } while (FindNextFileW(h_find, &find_data) != 0);

    FindClose(h_find);
    free(search_word);
    return 0;
}
