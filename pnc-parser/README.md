# pnc-parser
Small program for parsing PNC banking data into CSV format for an Excel spreadsheet. The PNC data is simply copy and pasted off of the PNC account activity page into a file called data.txt.

Currently, data.txt should be in this format
1. Date
2. Description
3. Transaction amount
4. Catagory
5. Account balance

Note: Some manual changes may be needed (like splitting up lines), but any leading or ending whitespace and dollar signs should be remove programmatically.

To execute this program, compile parser.cpp and run the correspoding file with data.txt in the same directory. An output.txt file will be created with the CSV data.

When prompted, enter the year that the data is from so that the correct dates can be generated. Then select which transactions are positive and which are negative. A final output file is generated which contains the CVS formatted transactions.

Note: Transactions are manually marked so that the program doesn't have to rely on things like tab positions to decide if a transaction is for a positive or negative amount. This makes the program more robust if the PNC website's layout changes.
