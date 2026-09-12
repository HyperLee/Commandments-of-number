# Commandments-of-number

這個專案是 `Commandments-of-1` 到 `Commandments-of-8` 的集中教材入口。每個子資料夾保留一份上游 C 語言範例與對應的繁體中文教學 README，讓讀者可以在同一個 repository 內由基礎輸入、字串與整數，一路讀到動態記憶體與指標。

## 1. 專案目的

這 8 個範例不是一套已經現代化的函式庫，而是用來觀察 C 語言常見語法、記憶體模型與錯誤模式的練習題。原始程式碼刻意以目前上游版本保留；安全替代寫法、平台差異與現代編譯器的限制，放在各題 README 中說明。

本專案的閱讀順序建議如下：

1. 先閱讀本頁的題目索引，建立 8 題的全貌。
2. 打開題目 README，先看學習目標，再對照原始碼。
3. 閱讀逐段解說與限制，不要把舊式範例直接當成生產環境程式碼。
4. 最後依各題的編譯與執行章節，在隔離的輸出目錄中嘗試驗證。

## 2. 目錄結構

```text
Commandments-of-number/
├── README.md
├── Commandments-of-1/
│   ├── README.md
│   └── Code/dragon1.cpp
├── Commandments-of-2/
│   ├── README.md
│   └── Code/dragon2.cpp
├── Commandments-of-3/
│   ├── README.md
│   └── Code/dragon3.cpp
├── Commandments-of-4/
│   ├── README.md
│   └── Code/dragon4.cpp
├── Commandments-of-5/
│   ├── README.md
│   └── Code/dragon5.cpp
├── Commandments-of-6/
│   ├── README.md
│   └── Code/dragon6.cpp
├── Commandments-of-7/
│   ├── README.md
│   └── Code/dragon7.cpp
└── Commandments-of-8/
    ├── README.md
    └── Code/dragon8.cpp
```

每一題只有題目根目錄的一份 README；`Code/` 子資料夾專門保存原始碼，不另外複製文件。

## 3. 題目索引與主題表

| 題目 | 主要概念 | 教學文件 | 原始碼 |
| --- | --- | --- | --- |
| 1 | `fgets`、字元陣列與輸入換行 | [Commandments-of-1 README](./Commandments-of-1/README.md) | [dragon1.cpp](./Commandments-of-1/Code/dragon1.cpp) |
| 2 | `gets` 與固定大小緩衝區溢位 | [Commandments-of-2 README](./Commandments-of-2/README.md) | [dragon2.cpp](./Commandments-of-2/Code/dragon2.cpp) |
| 3 | 字串常值與可修改字元陣列 | [Commandments-of-3 README](./Commandments-of-3/README.md) | [dragon3.cpp](./Commandments-of-3/Code/dragon3.cpp) |
| 4 | `strcat` 與目的緩衝區容量 | [Commandments-of-4 README](./Commandments-of-4/README.md) | [dragon4.cpp](./Commandments-of-4/Code/dragon4.cpp) |
| 5 | 有號/無號整數與轉型時機 | [Commandments-of-5 README](./Commandments-of-5/README.md) | [dragon5.cpp](./Commandments-of-5/Code/dragon5.cpp) |
| 6 | `SQUARE` 巨集與參數展開 | [Commandments-of-6 README](./Commandments-of-6/README.md) | [dragon6.cpp](./Commandments-of-6/Code/dragon6.cpp) |
| 7 | `malloc`、heap 記憶體與大量輸出 | [Commandments-of-7 README](./Commandments-of-7/README.md) | [dragon7.cpp](./Commandments-of-7/Code/dragon7.cpp) |
| 8 | 動態陣列回傳、指標位移與所有權 | [Commandments-of-8 README](./Commandments-of-8/README.md) | [dragon8.cpp](./Commandments-of-8/Code/dragon8.cpp) |

## 4. 共通編譯與執行方式

這些檔案使用 `.cpp` 副檔名，但內容是 C 語言範例。使用 Clang 時應以 `-x c` 明確指定語言，避免編譯器依副檔名把它當成 C++：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic \
  Commandments-of-1/Code/dragon1.cpp \
  -o /tmp/commandments-dragon1
```

只做語法檢查、不產生執行檔時，可以使用：

```bash
clang -x c -std=c11 -Wall -Wextra -pedantic -fsyntax-only \
  Commandments-of-1/Code/dragon1.cpp
```

將 `1` 與檔名替換成其他題號即可。各題 README 會指出該題在現代 C 標準下可能出現的編譯診斷。執行檔建議輸出到 `/tmp` 或其他隔離目錄，避免把產物放進 repository。

## 5. C 版本、平台與安全性提醒

- `dragon2.cpp` 使用已從現代 C 標準移除的 `gets`；它不接收緩衝區大小，輸入過長時可能覆寫記憶體。
- 多數範例呼叫 `system("pause")`。這是 Windows 命令，macOS 或 Linux 通常找不到 `pause`，不能視為可攜的等待方式。
- 第 7 題會配置 10,000,000 個 `int` 並逐筆輸出；記憶體與終端機輸出都可能造成很大的成本。
- 第 7、8 題配置的 heap 記憶體沒有在原始程式中 `free`；這些範例適合觀察配置與指標，不適合作為完整資源管理範本。
- README 中的安全寫法是教學對照，不代表原始 `.cpp` 已被修正。原始檔案在匯入時保持上游內容。

## 6. 上游 repo、分支與 commit SHA

以下是本次匯入快照所對應的上游 `main` commit。要同步新版本時，請先更新這張表與各題 README 的來源章節，再重新核對原始碼內容。

| 題目 | 上游 repo | 分支 | 匯入 commit |
| --- | --- | --- | --- |
| 1 | [HyperLee/Commandments-of-1](https://github.com/HyperLee/Commandments-of-1) | `main` | `0caf95832e8b2c669b63cadc52d100ba9b9ae1cd` |
| 2 | [HyperLee/Commandments-of-2](https://github.com/HyperLee/Commandments-of-2) | `main` | `81b1f5fc0df2f14fec91363737c708237f43be8e` |
| 3 | [HyperLee/Commandments-of-3](https://github.com/HyperLee/Commandments-of-3) | `main` | `89b4a66835f06e0ab037c0678423d3186afce1bb` |
| 4 | [HyperLee/Commandments-of-4](https://github.com/HyperLee/Commandments-of-4) | `main` | `1d0939d34e796cdfbc0ec01667cdc2994eb45a4a` |
| 5 | [HyperLee/Commandments-of-5](https://github.com/HyperLee/Commandments-of-5) | `main` | `ad41d51fe6fa9c1cd7d1e25623cf6ae75fcdc164` |
| 6 | [HyperLee/Commandments-of-6](https://github.com/HyperLee/Commandments-of-6) | `main` | `638eb5561d8504edb195d2ea2ad64ddf02c4b0f3` |
| 7 | [HyperLee/Commandments-of-7](https://github.com/HyperLee/Commandments-of-7) | `main` | `afddf87bd3b64846d266a9fc4845ee51a08871ec` |
| 8 | [HyperLee/Commandments-of-8](https://github.com/HyperLee/Commandments-of-8) | `main` | `ef522719af4c41bcbe46df7931e67964d6adb81e` |

## 7. 閱讀與後續同步方式

新增題目時，請沿用「題目資料夾 → `README.md` + `Code/` 原始碼」的結構，並在本頁題目索引加入相對連結。更新上游題目時，請依序完成下列工作：

1. 記錄新的上游 commit SHA。
2. 只替換對應的原始碼快照，先保留舊版文件內容作為比對依據。
3. 重新檢查 README 的程式碼解說、執行結果與安全性提醒是否仍符合原始碼。
4. 以 `git diff --check`、相對連結檢查與隔離編譯檢查確認變更範圍。

原始題目資訊可由各題 README 的「上游來源」章節追溯；本外層 repo 不保留 8 個巢狀 `.git` 歷史。
