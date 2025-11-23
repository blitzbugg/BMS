```md
# Bank Management System (C Project)

## MCA 2024–2026  
**Department of Computer Applications**  
**Mar Athanasios College for Advanced Studies, Tiruvalla (MACFAST)**  
**Faculty Coordinator:** Ms. Kripa Thankachan  

---

## 📌 Project Overview
This is a simple **Bank Management System** implemented in **C language** as part of the MCA first-year curriculum.  
The system performs basic file-based operations on three separate data files:

1. **Account Master File**  
2. **Transaction File**  
3. **Loan File**

Each module supports:
- Insert a record  
- Edit a record  
- Delete a record  
- View records  

All data is stored using **binary files (.dat)**.

---

## 📂 Project Structure

```

BankManagementSystem/
│
├── include/
│   ├── account.h
│   ├── transaction.h
│   ├── loan.h
│
├── src/
│   ├── main.c
│   ├── account.c
│   ├── transaction.c
│   ├── loan.c
│
├── data/
│   ├── account.dat
│   ├── transaction.dat
│   ├── loan.dat
│
└── README.md

```

---

## 🗂️ Data File Formats

### 1. Account Master File (`account.dat`)
| Field | Variable | Type |
|-------|----------|------|
| Account Number | a_no | int |
| Account Holder Name | a_name | char[20] |
| Address | a_addr | char[40] |
| Balance | a_bal | int |

### 2. Transaction File (`transaction.dat`)
| Field | Variable | Type |
|-------|----------|------|
| Transaction ID | t_id | int |
| Account Number | a_no | char[20] |
| Date | t_date | char[10] |
| Type (Credit/Debit) | t_type | int |
| Amount | t_amt | int |

### 3. Loan File (`loan.dat`)
| Field | Variable | Type |
|-------|----------|------|
| Loan ID | l_id | int |
| Account Number | a_no | int |
| Loan Date | l_date | char[10] |
| Loan Type | l_type | char[20] |
| Loan Amount | l_amt | int |
| Duration | l_dur | int |

---

## ▶️ How to Run
1. Compile all `.c` files together (example for GCC):

```

gcc src/*.c -o bank

```

2. Run the program:

```

./bank

```

The program will automatically create `.dat` files inside the **data/** folder if they do not exist.

---

## ✔️ Features Implemented
- File-based storage using binary files  
- Simple interactive menu system  
- CRUD operations for all three modules  
- Independent data handling for each file  

---

## 📌 Notes
- This project strictly follows the **exact specification** provided by the MCA department.  
- No advanced validation or banking logic is included, as per project requirement.  
- The purpose is to understand **file handling**, **structures**, and **modular programming** in C.

---

## 👤 Contributors
**Group Members – MCA 2025–2027 Batch**

Ananthapadmanabhan M
Abel Varghese John
Akhil S Kumar
Aparna Mohan
Aswin Baiju
Gadha Sathyan
Janisha J
Josson Jose Joseph
Malavika Subhash
Pranav M P
Rojin V Saji
Smera thankam Rojan



```

