#include<iostream>
#include<sqlite3.h> 
#include<string>
using namespace std;

class DBHandler{
private:
		string dbname="beatles.db";
		sqlite3 *db;
		char* sql;
		int rc;
		char *zErrMsg;
		sqlite3_stmt *stmt;
		static int callback(void *NotUsed, int argc, char **argv, char **azColName) {


		    for(int i = 0; i < argc; i++) {
		        cout << azColName[i] << ": " << argv[i] << endl;
		    
		    }

		  
		    cout << endl;

		    return 0;
		}
		void checkDBErrors() {

			if(rc){
				cout << "DB Error: " << sqlite3_errmsg(db) << endl;
		       	closeDB();
		        }
		    }
	public:
		DBHandler(){
		rc = sqlite3_open(dbname, &db);

    	checkDBErrors();
    
		}

		~DBHandler();
	void query(string query){

	rc = sqlite3_exec(db,query, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
   }
}

};