SQL: structured query language pronounced SQL or sequel. 

## Creating and Removing databases
- Creating a new database
```sql 
CREATE DATABASE <name_of_db>;
```
- deleting a database 
```sql
DROP DATABASE <name_of_db>;
```
## Tables
Tables are a part of a database where they contain information a db can hold many tables for example:
A blog database where it contains many tables: User-name, Phone number, Email, Credit card, Password etc..
![[Tables-exmaple.png]]
Notice how a table contains rows and columns.
The first Row contains the first costumer information 
The first column contains customer_id informations and such 
- Creating a new table 
```sql 
CREATE TABLE <table_name>( 
	ID int NOT NULl,
	name varchar(255) NOT NULL,
	email varchar(255),
	PRIMARY KEY(ID)
);
```
Alright a lot happened above creating a table we used `CREATE TABLE <table_name>`
Then we specified the internal informations, and it follows this syntax: name type options, mainly we start with the id since which would be different and unique for each users, and this where the primary key comes into play as we need to tell the db that this key should be unique.
- Deleting a table 
```sql 
DROP TABLE <table_name>;
```
- editing a table 
```sql 
ALTER TABLE <table_name>
	ADD name type;
```
## Inserting  information 
- Inserting information 
```sql 
INSERT INTO users(name,email,age)
VALUES ('tester','tester@gmail.com',69);
```
- Updating table 
```sql 
UPDATE table_name
```
- Setting stuff up 
```sql 
SET name='Tst',email 'fake@gmail.com'
WHERE ID=3;
```
- This will set the values given in where is equal to 3 
## Deleting informations 
- Similar to above
```sql 
DELETE FROM <table_name> WHERE <column/row>=something;
```
## Select 
Select is kinda like the print command for sql we just tell it where and what to get and then it will give us that information.
For example this will return every value from table of users: 
```mysql 
SELECT * FROM user; 
```
We can also use `WHERE` to chose a keyword or a value 
```mysql 
SELECT * FROM user 
WHERE NAME='SeaPiss';
```
Or we can search for something like this: 

```sql 
SELECT name, email 
FROM users 
```
Go ahead and play with it. 
## Cheat cheat 
To select two elements from a table use this as follows:
```sql 
SELECT name,age FROM <table_name>;
```
To eliminate duplicate words or values we use distinct key word.
The syntax for using distinct is as follows: 
```sql 
SELECT distinct column1 FROM table_name WHERE condition;
```