# Commandments-of-3

本題用兩種宣告方式對照「指向字串常值的指標」與「由字串常值初始化的字元陣列」。上游 README 標記為 Q3；原始檔案保留註解中的錯誤示例，讓讀者可以辨識哪些寫法只適合討論、哪些程式碼真的會執行。

## 1. 題目與學習目標

本題的核心問題是：看到 "john" 時，儲存的是可修改的陣列，還是不可修改的字串常值？完成閱讀後應能區分：

- char *pc = "john" 的指標與字串常值。
- char pc[] = "john" 建立出的可修改陣列。
- 變更字串第一個字元時，哪一種宣告有定義良好的行為。
- const 如何表達「不透過這個指標修改內容」的意圖。

## 2. 原始程式碼

完整檔案位於 [Code/dragon3.cpp](./Code/dragon3.cpp)。程式目前真正執行的部分是：

```c
char pc[] = "john";
printf("%s ", pc);
*pc = 'J';
printf("%s ", pc);
```

檔案前方的 char* pc 區塊被註解起來，並不是目前的執行路徑；它是原始題目留下的比較材料。

## 3. 逐段解說

### char *pc = "john"

這種宣告讓 pc 指向字串常值。字串常值的儲存位置不能由程式修改；即使某些舊環境把它放在可寫記憶體，嘗試透過 pc 改寫仍是未定義行為。比較清楚的現代寫法是：

```c
const char *literal = "john";
```

const 不會把指標本身變成不可重新指向，而是表達「不可透過這個指標修改它所指向的字元」。

### char pc[] = "john"

這次是建立一個陣列，並把字串常值的字元複製進去。陣列內容包含 j、o、h、n 與結尾的 \0，因此 *pc = 'J' 會把第一個字元改成大寫 J。

### 註解中的錯誤

註解區出現 *pc = "J" 與 prinf。前者把字串常值指定給單一 char，型別不相容；後者是 printf 的拼字錯誤。因為它們位於註解內，所以不會影響目前的執行，但不應誤當成可編譯的修正版。

## 4. 執行結果與可觀察行為

目前未註解的路徑先印出原字串，再修改第一個字元：

```text
john John[space]
```

`[space]` 表示第二次 `printf("%s ", pc)` 留下的一個尾端空格；用可見標記呈現可以避免文件自己的尾端空白被 Markdown 或 Git 工具忽略。

兩段輸出都沒有自行印換行，只有尾端的 system("pause") 可能在 Windows 顯示等待提示；其他平台可能顯示找不到命令。

## 5. 安全性、可攜性與限制

- 不要修改 char *pc = "john" 指向的字串常值；應使用 const char * 表達只讀用途。
- char pc[] = "john" 的陣列大小由初始化內容決定，目前是 5 bytes；若要放入更長文字，必須重新檢查容量。
- main(void) 缺少現代 C 慣用的 int 回傳型別；本題保留上游寫法，不把它改成另一份程式。
- system("pause") 依賴 Windows 命令，無法作為跨平台等待機制。

## 6. 概念上的安全寫法

把只讀資料與可修改資料分開命名，可以降低誤用機率：

```c
const char *literal = "john";
char word[] = "john";

word[0] = 'J';
printf("%s\n", word);
```

若內容需要在執行期間改變，應讓它位於有足夠容量的陣列或明確管理的動態記憶體中，而不是依賴字串常值的可寫性。

## 7. 複雜度與資源

這個範例只處理固定長度的 john：

- 修改與兩次輸出的時間可視為 O(1)；若以字串長度 L 泛化，輸出成本是 O(L)。
- pc 陣列使用 5 bytes 儲存字串與 \0，額外空間是固定 O(1)。
- 不涉及 heap 配置；system 的平台行為不改變字串操作本身的複雜度。

## 8. 編譯與執行

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic -fsyntax-only \
  Commandments-of-3/Code/dragon3.cpp
```

現代編譯器可能因原始的 main(void) 宣告報錯或警告。這是上游快照的相容性訊息；本次文件化不修改它。若只想驗證字串概念，可在獨立練習檔使用第 6 節的安全寫法。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-3](https://github.com/HyperLee/Commandments-of-3)
- 原始題目參考：[PTT C_and_CPP 討論串](https://www.ptt.cc/bbs/C_and_CPP/M.1465304337.A.9F2.html)
- 匯入分支：main
- 匯入 commit：[89b4a66835f06e0ab037c0678423d3186afce1bb](https://github.com/HyperLee/Commandments-of-3/commit/89b4a66835f06e0ab037c0678423d3186afce1bb)
- 上游檔案：[Code/dragon3.cpp](https://github.com/HyperLee/Commandments-of-3/blob/89b4a66835f06e0ab037c0678423d3186afce1bb/Code/dragon3.cpp)
