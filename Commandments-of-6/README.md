# Commandments-of-6

本題示範以巨集定義平方運算，並使用 SQUARE(10-5) 觀察前置處理器的文字展開。上游 README 標記為 Q6；本頁會把括號、運算優先序、重複求值與 inline function 的取捨拆開說明。

## 1. 題目與學習目標

閱讀本題後應能回答：

- 為什麼巨集定義中的參數與整體結果都要加括號？
- SQUARE(10-5) 實際會展開成什麼？
- 為什麼帶有副作用的引數不適合傳給這個巨集？
- 何時應以 static inline function 取代函式型巨集？

## 2. 原始程式碼

完整檔案位於 [Code/dragon6.cpp](./Code/dragon6.cpp)：

```c
#define SQUARE(x)    ((x) * (x))

int main()
{
    printf("%d\n", SQUARE(10-5));
    system("pause");
    return 0;
}
```

巨集使用雙層括號，這正是本題要觀察的重點。

## 3. 逐段解說

### 前置處理器展開

在編譯器正式解析 C 語法前，前置處理器會把 SQUARE(10-5) 以文字方式替換成：

```c
((10-5) * (10-5))
```

所以每個 10-5 都先完成減法，最後得到 25。參數括號避免呼叫者傳入包含加減法的表達式時被外部運算子改變結合方式，整體括號則避免巨集放進更大的算式時被截斷。

### 重複求值

括號只能處理優先序，不能消除 x 被替換兩次的事實。例如 SQUARE(i++) 會把 i++ 放進兩個運算位置；這會造成兩次遞增及未定義行為，不應使用。

### 型別與除錯

巨集沒有函式真正的參數型別檢查，也沒有函式呼叫的單一求值語意。除錯時看到的是展開後的程式，而不是一個可在 debugger 中自然觀察的函式邊界。

## 4. 執行結果與可觀察行為

SQUARE(10-5) 的主輸出為：

```text
25
```

程式結尾呼叫 system("pause")；在 Windows 可能等待使用者按鍵，在 macOS 或 Linux 通常會顯示找不到 pause 的訊息。

## 5. 安全性、可攜性與限制

- 不要把 i++、函式呼叫或其他有副作用的運算式傳給此巨集。
- 巨集可能接受不同型別，但結果是否符合預期要由呼叫者自己負責。
- 巨集名稱可能污染整個翻譯單元；大型專案需特別注意命名衝突。
- system("pause") 是平台相依的 shell 命令，也不是通用的程式等待 API。
- 原始程式沒有使用型別更精確的平方函式，也沒有處理整數溢位；本頁只說明原始行為。

## 6. 概念上的安全寫法

對固定型別的整數平方，可以用 inline function 讓引數只求值一次：

```c
static inline int square_int(int value)
{
    return value * value;
}

int result = square_int(10 - 5);
```

若平方結果可能超出 int，還要先決定應使用更寬的型別、檢查範圍，或定義錯誤處理策略。inline 只是函式的編譯最佳化提示，不是整數溢位檢查。

## 7. 複雜度與資源

目前輸入是兩個常值運算：

- 減法與乘法的時間複雜度為 O(1)。
- 不需要依輸入大小成長的額外空間，為 O(1)。
- 巨集展開會複製表達式文字；若傳入很大的複雜表達式，編譯期文字量可能增加，但本例可忽略。

## 8. 編譯與執行

檔案副檔名是 .cpp，但應以 C 語言編譯：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic \
  Commandments-of-6/Code/dragon6.cpp \
  -o /tmp/commandments-dragon6
/tmp/commandments-dragon6
```

若只需要確認語法，可將編譯指令改成加上 -fsyntax-only。非 Windows 平台執行時，請把 pause 訊息視為原始快照的可攜性限制。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-6](https://github.com/HyperLee/Commandments-of-6)
- 匯入分支：main
- 匯入 commit：[638eb5561d8504edb195d2ea2ad64ddf02c4b0f3](https://github.com/HyperLee/Commandments-of-6/commit/638eb5561d8504edb195d2ea2ad64ddf02c4b0f3)
- 上游檔案：[Code/dragon6.cpp](https://github.com/HyperLee/Commandments-of-6/blob/638eb5561d8504edb195d2ea2ad64ddf02c4b0f3/Code/dragon6.cpp)
