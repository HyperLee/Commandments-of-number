# Commandments-of-5

本題示範有號整數與無號整數混合運算時，轉型發生的時間點會如何改變結果。上游 README 標記為 Q5；本頁特別拆開「先運算再轉型」與「先轉型再運算」兩種情況。

## 1. 題目與學習目標

閱讀本題後應能回答：

- 為什麼把整個算式包在轉型中，不能挽救算式內已經發生的 signed overflow？
- 為什麼把其中一個運算元先轉成 unsigned，會讓整個運算改用 unsigned 規則？
- unsigned 整數超過最大值時，什麼是 modulo 2^N 行為？
- printf 的 %u 為什麼要和 unsigned int 對應？

## 2. 原始程式碼

完整檔案位於 [Code/dragon5.cpp](./Code/dragon5.cpp)。核心部分如下：

```c
//unsigned int sum = 2000000000 + 2000000000;  /* 超出 int 存放範圍 */
//unsigned int sum = (unsigned int) (2000000000 + 2000000000);
unsigned int sum = (unsigned int) 2000000000 + 2000000000;

printf("sum:%u\n", sum);
```

前兩行保留為註解，分別展示轉型發生在整個算式之前或之後的差異；目前真正執行的是第三種寫法。

## 3. 逐段解說

### 先運算再指定

2000000000 + 2000000000 中的兩個整數常值通常先以 signed int 參與運算。在 32 位元 int 環境中，總和 4,000,000,000 超過 signed int 的最大值 2,147,483,647，因此在轉成 unsigned int 之前就已經發生 signed overflow。這是未定義行為，不是可靠的「先算出負數再轉正」。

所以，下列寫法的外層轉型太晚：

```c
(unsigned int)(2000000000 + 2000000000)
```

### 先轉型再運算

目前的寫法先把左側常值轉成 unsigned int：

```c
(unsigned int)2000000000 + 2000000000
```

依照 C 的 usual arithmetic conversions，另一個運算元也會轉成相容的 unsigned 型別，整個加法就使用 unsigned arithmetic。若 unsigned int 是常見的 32 位元型別，結果是 4,000,000,000；這個值仍在 unsigned int 的可表示範圍內。

### %u

printf 的 %u 期待的是 unsigned int。原始變數宣告為 unsigned int，因此格式指定字元與引數型別相符；若改用其他寬度的整數型別，就要改用相應的格式化方式。

## 4. 執行結果與可觀察行為

在 unsigned int 至少能表示 4,000,000,000 的常見環境中，主輸出為：

```text
sum:4000000000
```

這個數值不是因為 unsigned 具有無限容量，而是因為目前的結果仍在該型別範圍內。若 unsigned 運算再超過最大值，會依模數折返；模數是該型別的最大值加一。

## 5. 安全性、可攜性與限制

- C 標準只保證 unsigned int 至少有 16 位元；不要在沒有確認型別寬度時硬編碼「一定是 32 位元」的結論。
- signed overflow 是未定義行為；把轉型寫在整個算式外面不會修復它。
- unsigned wraparound 是定義好的 modulo 行為，但不代表業務邏輯一定正確。
- 原始程式包含未使用的 stdlib.h；它不影響這個整數運算示例。
- 本題沒有 system("pause")，但輸出結果仍可能因整數寬度與編譯器診斷而需要環境說明。

## 6. 概念上的安全寫法

若目標只是讓運算從一開始就使用 unsigned，可以讓常值或中間變數明確成為 unsigned：

```c
unsigned int left = 2000000000U;
unsigned int right = 2000000000U;
unsigned int sum = left + right;
printf("sum:%u\n", sum);
```

若需求是精確的 32 位元資料，應考慮 uint32_t，並使用 stdint.h 與對應的 inttypes.h 格式，而不是假設 unsigned int 的寬度。

## 7. 複雜度與資源

本題只做一次加法與一次輸出：

- 時間複雜度：O(1)。
- 額外空間：固定數量的整數變數，為 O(1)。
- 數值範圍：結果是否可表示取決於 unsigned int 的實際寬度；overflow 後才會進入 modulo 折返。

## 8. 編譯與執行

檔案副檔名雖為 .cpp，仍以 C 語言檢查：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic \
  Commandments-of-5/Code/dragon5.cpp \
  -o /tmp/commandments-dragon5
/tmp/commandments-dragon5
```

也可以先用 -fsyntax-only 只做語法檢查。實際輸出應依執行環境的整數寬度記錄，不要把某台機器的位元寬度當成 C 標準保證。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-5](https://github.com/HyperLee/Commandments-of-5)
- 匯入分支：main
- 匯入 commit：[ad41d51fe6fa9c1cd7d1e25623cf6ae75fcdc164](https://github.com/HyperLee/Commandments-of-5/commit/ad41d51fe6fa9c1cd7d1e25623cf6ae75fcdc164)
- 上游檔案：[Code/dragon5.cpp](https://github.com/HyperLee/Commandments-of-5/blob/ad41d51fe6fa9c1cd7d1e25623cf6ae75fcdc164/Code/dragon5.cpp)
