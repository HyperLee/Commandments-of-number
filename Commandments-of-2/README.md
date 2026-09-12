# Commandments-of-2

本題是固定大小字元陣列與不安全輸入函式的反例。上游 README 標記為 Q3，並連到 C/C++ 討論串；本頁保留來源脈絡，重點放在理解為什麼 gets 不能被當成安全的字串輸入工具。

## 1. 題目與學習目標

閱讀本題後應能回答：

- char name[21] 真正能保證保存多少內容？
- 為什麼 gets(name) 無法知道目的陣列的容量？
- 為什麼現代 C 標準不再提供 gets？
- 如何用 fgets 取代它，並處理換行與過長輸入？

## 2. 原始程式碼

完整檔案請直接查看 [Code/dragon2.cpp](./Code/dragon2.cpp)。關鍵執行片段是：

```c
char name[21];   /* Max Length 20 + one empty '\0' */
printf("Your name, please: ");
gets(name);
printf("Hello, %s\n", name);
```

原始檔案另含上游的舊編碼註解與舊式 main 宣告；本文件不轉碼或修改該檔案。

## 3. 逐段解說

### char name[21]

若輸入限制確實是 20 個可見字元，還要多 1 個位置存放字串結尾的 \0，所以才會看到 21。這個數字本身不會自動限制使用者輸入；它只表示陣列實際配置的大小。

### gets(name)

gets 只收到一個指標，不收到陣列容量。它會持續從標準輸入讀取，直到換行，卻沒有可靠方式知道 name 還剩多少空間。輸入超過 20 個可見字元時，函式仍可能把資料與結尾字元寫到陣列之外，覆寫鄰近記憶體。

這不是「使用者輸入太長時結果不漂亮」而已，而是未定義行為：可能造成資料損壞、程式崩潰，甚至形成安全漏洞。

### 現代標準的影響

gets 因為無法安全使用，已從 C11 移除。使用現代編譯器時，常見結果是函式未宣告警告、連結失敗或直接被工具拒絕。這個現象正好說明 API 設計上的問題，但不應透過修改原始快照來掩蓋。

## 4. 執行結果與可觀察行為

在舊式、仍提供 gets 的環境中，短輸入可能看起來正常：

```text
Your name, please: Alice
Hello, Alice
```

「短輸入能正常輸出」不能證明程式安全；它只代表這一次輸入沒有立刻越過陣列邊界。長輸入的結果不可預測，不應以實際攻擊字串測試於重要環境。

## 5. 安全性、可攜性與限制

- gets 沒有長度參數，存在明確的緩衝區溢位風險。
- C11 已移除 gets；現代 macOS 編譯器不應把它當成可攜 API。
- main(void) 沒有寫出回傳型別，是早期 C 寫法；現代程式應使用 int main(void)，但本次不修改上游程式。
- 原始程式沒有檢查輸入錯誤，也沒有說明長度超過限制時要如何處理。
- 本題不應使用 gets 的任何變形或自行包裝來繞過長度檢查。

## 6. 概念上的安全寫法

可用 fgets 明確把陣列大小傳入，再視需要移除換行：

```c
if (fgets(name, sizeof name, stdin) == NULL) {
    return 1;
}

name[strcspn(name, "\n")] = '\0';
```

這需要 string.h 的 strcspn。若一整行可能長於陣列，還要檢查是否真的讀到換行，並清理剩餘輸入或改用動態儲存；fgets 只解決「不越界」，不會自動完成完整輸入政策。

## 7. 複雜度與資源

令輸入長度為 L：

- 理想的讀取與輸出時間是 O(L)。
- 原始陣列固定配置 21 bytes，額外空間是 O(1)。
- 當 L > 20 時，原始程式的行為不再有可分析的合法上限，因為已進入緩衝區溢位與未定義行為。

## 8. 編譯與執行

可先用現代 C 標準觀察診斷，不要把失敗訊息改寫成成功：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic -fsyntax-only \
  Commandments-of-2/Code/dragon2.cpp
```

若要研究短輸入的舊式行為，應使用隔離環境並先確認工具鏈是否提供 gets。不要在真實服務、含敏感資料的終端機或共享環境中測試超長輸入。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-2](https://github.com/HyperLee/Commandments-of-2)
- 原始題目參考：[PTT C_and_CPP 討論串](https://www.ptt.cc/bbs/C_and_CPP/M.1465304337.A.9F2.html)
- 匯入分支：main
- 匯入 commit：[81b1f5fc0df2f14fec91363737c708237f43be8e](https://github.com/HyperLee/Commandments-of-2/commit/81b1f5fc0df2f14fec91363737c708237f43be8e)
- 上游檔案：[Code/dragon2.cpp](https://github.com/HyperLee/Commandments-of-2/blob/81b1f5fc0df2f14fec91363737c708237f43be8e/Code/dragon2.cpp)
