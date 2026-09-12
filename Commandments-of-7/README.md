# Commandments-of-7

本題示範以 malloc 在 heap 配置一個很大的 int 陣列，逐格寫入並印出。上游 README 標記為 Q7；本頁把配置大小、失敗處理、輸出成本與釋放責任分開說明。

## 1. 題目與學習目標

閱讀本題後應能回答：

- 為什麼 10,000,000 個 int 不適合直接放在函式的 stack？
- malloc 成功與失敗時，array 指標分別代表什麼？
- 為什麼大量 printf 可能比陣列寫入更快成為瓶頸？
- 為什麼離開程式前仍應釋放 malloc 配置的記憶體？

## 2. 原始程式碼

完整檔案位於 [Code/dragon7.cpp](./Code/dragon7.cpp)：

```c
int i = 0;
//int array[10000000];
int *array = (int*) malloc(10000000*sizeof(int));

for(i = 0; i < 10000000; i++)
{
    array[i] = i;
    printf("array[%d] %d\n", i, array[i]);
}
```

註解中的區域陣列與實際的 malloc 版本是兩種不同的儲存位置示例；原始檔案本身保持不變。

## 3. 逐段解說

### stack 與 heap

若把 10,000,000 個 int 直接宣告成區域陣列，通常會對 stack 造成很大壓力。malloc 則向 heap 要求執行期間的動態記憶體，回傳一個可以保存陣列起始位置的指標。

配置的位元組數是 10,000,000 * sizeof(int)。在 int 為 4 bytes 的常見環境中，約為 40,000,000 bytes，也就是約 38.1 MiB；實際大小仍應以 sizeof(int) 為準。

### malloc 與陣列索引

成功時，array 指向連續配置的第一個 int。array[i] 會存取第 i 個元素，迴圈把索引值寫入同一個位置後立即印出。原始程式把 malloc 的 void 指標轉型成 int 指標；在 C 語言中通常不需要這個轉型。

### 輸出成本

迴圈會呼叫 10,000,000 次 printf。終端機 I/O 的成本非常高，實際執行可能需要很久，甚至讓人誤以為記憶體配置失敗。這個範例同時展示了資料處理與輸出策略的差別。

## 4. 執行結果與可觀察行為

成功配置且允許大量輸出的環境，開頭幾行會像：

```text
array[0] 0
array[1] 1
array[2] 2
...
```

完整執行會嘗試印出從 array[0] 到 array[9999999] 的所有行。不要把完整輸出重導到不受控的檔案或終端機；測試時可以只觀察前幾行，或先複製程式到獨立練習檔縮小迴圈。

## 5. 安全性、可攜性與限制

- 原始程式沒有檢查 malloc 是否回傳 NULL；配置失敗後解參考 array 會造成錯誤。
- 原始程式沒有呼叫 free(array)，因此配置的 heap 記憶體沒有明確釋放。
- 10,000,000 * sizeof(int) 的實際大小取決於 int 寬度與平台可用記憶體。
- int i 在目前的 10,000,000 上限通常足夠，但以 size_t 表示陣列大小與索引更符合 C 的記憶體 API。
- system("pause") 依賴 Windows 命令；而且在大量輸出完成前通常不容易到達該行。

## 6. 概念上的安全寫法

動態配置至少應檢查失敗並使用 sizeof *array 避免重複型別名稱：

```c
size_t count = 10000000;
int *array = malloc(count * sizeof *array);
if (array == NULL) {
    return 1;
}

for (size_t i = 0; i < count; i++) {
    array[i] = (int)i;
}

free(array);
```

實際應用還要檢查 count 與 sizeof *array 相乘是否溢位，並決定是否真的需要保存全部元素。若只是示範數值，不必把一千萬筆資料全部印到終端機。

## 7. 複雜度與資源

令元素數量為 N：

- 配置與初始化時間為 O(N)。
- 每筆 printf 也需要處理一次輸出，因此整體輸出成本至少是 O(N)，且常數成本很大。
- heap 空間為 N * sizeof(int)，即 O(N)。
- 原始程式額外需要一個 int 索引與一個指標，為 O(1) 的控制空間。

## 8. 編譯與執行

先做語法檢查，避免立刻產生大量輸出：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic -fsyntax-only \
  Commandments-of-7/Code/dragon7.cpp
```

若要真正執行，請使用隔離環境並預留約 10,000,000 行輸出的時間與儲存空間。macOS 或 Linux 上的 system("pause") 可能在最後另外顯示找不到命令。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-7](https://github.com/HyperLee/Commandments-of-7)
- 匯入分支：main
- 匯入 commit：[afddf87bd3b64846d266a9fc4845ee51a08871ec](https://github.com/HyperLee/Commandments-of-7/commit/afddf87bd3b64846d266a9fc4845ee51a08871ec)
- 上游檔案：[Code/dragon7.cpp](https://github.com/HyperLee/Commandments-of-7/blob/afddf87bd3b64846d266a9fc4845ee51a08871ec/Code/dragon7.cpp)
