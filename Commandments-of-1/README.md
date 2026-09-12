# Commandments-of-1

本題是以 C 語言讀取使用者姓名的入門範例。上游 README 的原始標記是 C Code、Q1，並提供一篇 C/C++ 討論連結；本頁保留這些來源資訊，再補上可以實際觀察的輸入行為與安全邊界。

## 1. 題目與學習目標

程式先建立一個固定大小的字元陣列，提示使用者輸入姓名，再把姓名印出來。閱讀本題要掌握：

- C 字串其實是以 \0 結尾的 char 陣列。
- fgets 的第二個參數是目的緩衝區容量。
- fgets 在讀到換行時通常會把換行字元一併存入陣列。
- 輸入長度超過緩衝區時，剩餘字元會留在 stdin，不會自動消失。

## 2. 原始程式碼

完整原始碼位於 [Code/dragon1.cpp](./Code/dragon1.cpp)。核心片段如下：

```c
char name[20];
printf("enter ypur name: ");
//scanf("%s", name);
fgets(name,20,stdin);
printf("hello ,%s\n", name);
```

原始程式中的 ypur 拼字、空格與註解都保持不變；它們是快照的一部分，不是本次文件化工作要修正的內容。

## 3. 逐段解說

### char name[20]

陣列共有 20 個 char 位置。若要存放一般 C 字串，最後還要預留一個 \0，因此在不含換行的理想情況下最多放 19 個可見字元。

### fgets(name, 20, stdin)

fgets 最多讀取 20 - 1 個字元，並在成功讀取時補上 \0。如果使用者輸入的換行在這個容量內，換行也會被保存。例如輸入 Alice 後按 Enter，陣列概念上會接近：

```text
'A' 'l' 'i' 'c' 'e' '\n' '\0'
```

這與 scanf("%s", name) 不同：被註解的 scanf 版本不會讀取空白後的內容，而 %s 若沒有寬度限制也可能寫過陣列邊界。fgets 是較好的起點，但仍需處理回傳值與輸入殘留。

### printf("hello ,%s\n", name)

格式字串本身再加一個 \n。因為 fgets 可能已把 Enter 造成的換行放進 name，所以輸出姓名後通常會再多出一個空白行。

### system("pause")

這行依賴作業系統命令。pause 是 Windows 常見命令，在 macOS 或 Linux 通常不存在；它也會把字串交給 shell 執行，不適合作為可攜或安全的通用等待方式。

## 4. 執行結果與可觀察行為

輸入短姓名時，概念上的互動結果如下；system("pause") 在非 Windows 環境可能另外印出找不到命令的訊息：

```text
enter ypur name: Alice
hello ,Alice

```

如果輸入超過 19 個字元，fgets 只會先讀取能放入 name 的部分，下一次讀取仍可能取得同一行剩餘內容。這是「有界讀取」與「一次讀完一整行」之間的重要差別。

## 5. 安全性、可攜性與限制

- fgets 的長度參數寫成 20，與陣列大小同步；若日後修改陣列大小卻忘記修改參數，就會產生維護風險。
- 沒有檢查 fgets 的回傳值。遇到 EOF 或輸入錯誤時，不應直接把未成功讀取的內容當成有效字串。
- 程式沒有移除結尾換行，因此顯示格式會受輸入方式影響。
- system("pause") 是平台相依且可能帶來 shell 注入風險的做法。
- stdlib.h 只為 system 提供宣告；若移除等待行為，也應重新檢視是否仍需要這個標頭。

## 6. 概念上的安全寫法

保留原始範例不變時，可以把安全處理想成下列步驟：先以 sizeof name 限制讀取，再檢查回傳值，最後移除換行。strcspn 需要 string.h：

```c
if (fgets(name, sizeof name, stdin) == NULL) {
    return 1;
}

name[strcspn(name, "\n")] = '\0';
```

如果輸入可能長於陣列容量，還要明確決定要拒絕、清空剩餘輸入，或改用可擴充的儲存方式。

## 7. 複雜度與資源

令本次實際讀取的字元數為 L：

- 時間複雜度：O(L)，主要成本是讀取與輸出字串。
- 額外空間：固定 20 個 char，因此可視為 O(1)。
- 輸入上限：單次呼叫最多取得 19 個字元與結尾 \0，若包含換行，能放的可見字元會更少。

## 8. 編譯與執行

檔案副檔名是 .cpp，但內容應以 C 編譯。macOS 可明確指定 -x c：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic \
  Commandments-of-1/Code/dragon1.cpp \
  -o /tmp/commandments-dragon1
printf 'Alice\n' | /tmp/commandments-dragon1
```

若執行環境不是 Windows，最後的 system("pause") 訊息屬於原始程式的平臺差異，不代表 fgets 的讀取結果錯誤。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-1](https://github.com/HyperLee/Commandments-of-1)
- 原始題目參考：[PTT C_and_CPP 討論串](https://www.ptt.cc/bbs/C_and_CPP/M.1465304337.A.9F2.html)
- 匯入分支：main
- 匯入 commit：[0caf95832e8b2c669b63cadc52d100ba9b9ae1cd](https://github.com/HyperLee/Commandments-of-1/commit/0caf95832e8b2c669b63cadc52d100ba9b9ae1cd)
- 上游檔案：[Code/dragon1.cpp](https://github.com/HyperLee/Commandments-of-1/blob/0caf95832e8b2c669b63cadc52d100ba9b9ae1cd/Code/dragon1.cpp)
