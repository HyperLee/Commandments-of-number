# Commandments-of-8

本題示範由函式配置動態陣列並回傳指標，呼叫端再以陣列索引或指標位移寫入資料。上游 README 標記為 Q8；本頁特別說明回傳 heap 記憶體後的所有權、配置失敗與釋放責任。

## 1. 題目與學習目標

閱讀本題後應能回答：

- createNewArray(int size) 回傳的指標指向哪一段記憶體？
- ptr + i 與 *(ptr + i) 分別代表什麼？
- 為什麼呼叫端必須檢查 NULL 並在使用後呼叫 free？
- 為什麼 size 不能接受負數或未檢查的大數？

## 2. 原始程式碼

完整檔案位於 [Code/dragon8.cpp](./Code/dragon8.cpp)。核心部分如下：

```c
int* createNewArray(int size) {
    return (int*) malloc(size * sizeof(int));
}

ptr = createNewArray(10);

for(i = 0; i < 10 ; i++)
{
    *(ptr + i) = i;
    printf("ptr + %d = %d\n", i, *(ptr + i));
}
```

原始程式也保留被註解的 newArray(ptr, 10) 以及 system("pause")；本次不修改上游檔案。

## 3. 逐段解說

### createNewArray

函式使用 malloc 配置 size 個 int 所需的空間，回傳配置區域的起始位址。這個位址位於 heap，不是函式結束後就自動回收的區域變數。函式名稱雖然表達「建立新陣列」，但目前沒有把配置失敗或不合法 size 告訴呼叫端。

### ptr + i

如果 ptr 指向陣列第一個元素，C 的指標運算會依元素型別自動計算位移：ptr + 1 不是只前進 1 byte，而是前進 sizeof(int) bytes，指向下一個 int。

### *(ptr + i) 與 ptr[i]

對陣列指標而言，下列兩種寫法等價：

```c
*(ptr + i) = i;
ptr[i] = i;
```

第一種寫法把「位移後解參考」直接寫出來，適合教學指標運算；第二種通常更容易閱讀。

### 呼叫端的責任

createNewArray 回傳的是配置資源的所有權。呼叫端應先確認 ptr 不為 NULL，再使用它；使用完成後應呼叫 free(ptr)。原始範例沒有這兩個步驟，因此只展示了成功路徑。

## 4. 執行結果與可觀察行為

若配置成功，迴圈會印出 10 行：

```text
ptr + 0 = 0
ptr + 1 = 1
ptr + 2 = 2
ptr + 3 = 3
ptr + 4 = 4
ptr + 5 = 5
ptr + 6 = 6
ptr + 7 = 7
ptr + 8 = 8
ptr + 9 = 9
```

程式最後的 system("pause") 在 Windows 可能等待按鍵；macOS 或 Linux 通常會因找不到 pause 而產生額外訊息。

## 5. 安全性、可攜性與限制

- 沒有檢查 malloc 的回傳值；配置失敗時 ptr 可能是 NULL，解參考它會出錯。
- size 是 int。負數經過乘法與 size_t 轉換後，可能變成非常大的配置請求；應先拒絕負數。
- 沒有檢查 size * sizeof(int) 是否發生整數乘法溢位。
- 沒有呼叫 free(ptr)，因此原始程式有資源洩漏。
- 不應在函式回傳後使用已經釋放的指標，也不應對同一指標重複 free。
- system("pause") 是 Windows 相依的 shell 命令，不是跨平台等待方式。

## 6. 概念上的安全寫法

可讓尺寸使用 size_t，使用 sizeof *result，並把失敗交給呼叫端處理：

```c
int *createNewArray(size_t size)
{
    int *result = malloc(size * sizeof *result);
    return result;
}

int *ptr = createNewArray(10);
if (ptr == NULL) {
    return 1;
}

for (size_t i = 0; i < 10; i++) {
    ptr[i] = (int)i;
}

free(ptr);
```

完整版本還要在乘法前檢查 size 是否超過可配置上限，並明確規定 size 為 0 時要回傳 NULL、可釋放的指標，或直接拒絕。

## 7. 複雜度與資源

令配置的元素數量為 N：

- malloc 配置與初始化陣列的空間成本為 O(N)。
- 迴圈寫入並輸出每個元素，時間複雜度為 O(N)；終端機輸出通常是主要實際成本。
- heap 空間為 N * sizeof(int)，即 O(N)。
- 指標與索引等控制資料使用 O(1) 額外空間。

## 8. 編譯與執行

先做不執行程式的語法檢查：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic -fsyntax-only \
  Commandments-of-8/Code/dragon8.cpp
```

若建立執行檔，請把輸出放在隔離目錄。執行時應觀察 10 行資料，並把 system("pause") 的平台差異視為原始範例限制。

## 9. 上游來源

- Repo：[HyperLee/Commandments-of-8](https://github.com/HyperLee/Commandments-of-8)
- 匯入分支：main
- 匯入 commit：[ef522719af4c41bcbe46df7931e67964d6adb81e](https://github.com/HyperLee/Commandments-of-8/commit/ef522719af4c41bcbe46df7931e67964d6adb81e)
- 上游檔案：[Code/dragon8.cpp](https://github.com/HyperLee/Commandments-of-8/blob/ef522719af4c41bcbe46df7931e67964d6adb81e/Code/dragon8.cpp)
