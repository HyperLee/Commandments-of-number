# Commandments-of-4

本題示範使用 strcat 將兩段 C 字串接到同一個目的陣列。上游 README 只標記 Q4；本頁補充 strcat 的記憶體前提、容量計算、字串常值與跨平台執行限制。

## 1. 題目與學習目標

完成本題後應能說明：

- 為什麼 strcat 的第一個參數必須指向可修改且有足夠容量的陣列。
- 目前 s1[20] 為什麼剛好能容納 "Hello, " + "world!"。
- 為什麼 strcat 不會替呼叫者檢查目的陣列邊界。
- 為什麼來源字串指標應使用 const char * 表達只讀意圖。

## 2. 原始程式碼

完整檔案位於 [Code/dragon4.cpp](./Code/dragon4.cpp)。關鍵程式碼如下：

```c
char s1[20] = "Hello, ";
char *s2 = "world!";
strcat(s1, s2);
printf("%s\n", s1);
```

原始檔案也保留上游的舊編碼註解與 main(void) 宣告；本次不對原始碼轉碼或修正。

## 3. 逐段解說

### 目的陣列 s1

"Hello, " 有 7 個可見字元，結尾還需要 1 個 \0。"world!" 有 6 個可見字元，因此連接後需要：

```text
7 + 6 + 1 = 14 bytes
```

s1 有 20 bytes，所以這一組固定文字在目前案例中放得下，尚餘 6 bytes。這個結論只對目前內容成立；如果任一字串改長，就必須重新計算。

### 來源指標 s2

strcat 只讀取 s2，不會修改它，因此概念上應宣告成 const char *s2 = "world!"。原始程式使用 char *，在現代 C 中雖常見於舊程式，但沒有表達出「來源不可寫」的意圖。

### strcat(s1, s2)

函式會先找到 s1 原本結尾的 \0，從那個位置開始複製 s2 的字元，最後再放入新的 \0。它不會知道 s1 的總容量，也不會自動截斷；容量不足時就是越界寫入。

## 4. 執行結果與可觀察行為

目前文字長度足夠小，因此預期主輸出為：

```text
Hello, world!
```

離開前的 system("pause") 仍是原始程式的一部分；在 macOS 或 Linux 通常會因找不到 pause 而產生額外訊息。

## 5. 安全性、可攜性與限制

- 呼叫 strcat 前，必須證明 strlen(s1) + strlen(s2) + 1 <= sizeof s1。
- strcat 沒有目的緩衝區大小參數，不能單靠函式本身避免溢位。
- s1 必須是可寫陣列；把字串常值當成目的參數會導致未定義行為。
- s2 最好使用 const char *，避免讓呼叫者誤以為可以修改字串常值。
- main(void) 是舊式宣告，system("pause") 則是 Windows 相依命令；兩者都會影響現代跨平台編譯/執行。

## 6. 概念上的安全寫法

若要在一次格式化中完成連接，可以使用帶容量的函式並檢查回傳值：

```c
int written = snprintf(s1, sizeof s1, "%s%s", "Hello, ", "world!");
if (written < 0 || (size_t)written >= sizeof s1) {
    /* 輸出被截斷或格式化失敗 */
}
```

這個片段需要 stdio.h 與 size_t 的適當宣告。重點不是盲目改用另一個函式，而是讓目的容量成為 API 呼叫的一部分，並處理「放不下」的結果。

## 7. 複雜度與資源

令兩段字串長度分別為 n 與 m：

- strcat 需要先掃描目的字串，再複製來源字串，時間複雜度為 O(n + m)。
- 目的陣列固定配置 20 bytes，額外空間為 O(1)。
- 真正的安全前提是目的容量至少為 n + m + 1，其中最後的 1 是新的 \0。

## 8. 編譯與執行

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic -fsyntax-only \
  Commandments-of-4/Code/dragon4.cpp
```

這個指令只做語法與警告檢查，不會執行 system("pause")。若要建立執行檔，請把 -fsyntax-only 改成 -o /tmp/commandments-dragon4，並預期非 Windows 平台可能出現 pause 命令不存在的訊息。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-4](https://github.com/HyperLee/Commandments-of-4)
- 匯入分支：main
- 匯入 commit：[1d0939d34e796cdfbc0ec01667cdc2994eb45a4a](https://github.com/HyperLee/Commandments-of-4/commit/1d0939d34e796cdfbc0ec01667cdc2994eb45a4a)
- 上游檔案：[Code/dragon4.cpp](https://github.com/HyperLee/Commandments-of-4/blob/1d0939d34e796cdfbc0ec01667cdc2994eb45a4a/Code/dragon4.cpp)
