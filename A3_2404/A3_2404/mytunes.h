/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */
/*  Author:   (c) 2019 Louis Nel                     */
/*  All rights reserved.  Distribution and           */
/*  reposting, in part or in whole, requires         */
/*  written consent of the author.                   */
/*                                                   */
/*  COMP 2404 students may reuse this content for    */
/*  their course assignments without seeking consent */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MYTUNES_H
#define MYTUNES_H
#include <sstream>
#include <string.h>
using namespace std;
#include "UI.h"
#include "command.h"
#include "song.h"
#include "songs.h"
#include "recording.h"
#include "recordings.h"
#include "track.h"
#include "tracks.h"
//#include "playlist.h"
#include "user.h"
#include "users.h"
#include "sqlite3.h"
/*
This is the main application class.
It has knowlege of the UI and data model (not done in this assignment).
*/

class MyTunes
{
  public:
    MyTunes();
    void run();
    void executeCommand(Command cmd);
    //callback function to handle insert & delete queries
    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  	 int i;
   	for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  	 }
   		printf("\n");
   	return 0;
	}	

	//callback function to load initial data from database
	static int loadCallback(void *data, int argc, char **argv, char **azColName){

		char *tname=db_table_name;

		string cmdstr="add -";
		if(!strcmp(tname,"songs")){
			cmdstr+="s";
		}else if(!strcmp(tname,"recordings")){
			cmdstr+="r";
		}else if(!strcmp(tname,"tracks")){
			cmdstr+="t";
		}else if(!strcmp(tname,"users")){
			cmdstr+="u";
		}else if(!strcmp(tname,"playlists")){
			cmdstr+="p";
		}else if(!strcmp(tname,"playlist_tracks")){
			cmdstr+="l";
		}
		for(int i = 0; i<argc; i++) {
			string res=string(argv[i]);
			cmdstr=cmdstr+" "+res;
  		}
  		Command cmd(cmdstr);
  		mytunes->executeCMDADD(cmd);
		return 0;
	}
  private:
  	static char* db_table_name;
  	static MyTunes *mytunes;
    UI view;
	//Data Model
	//available ID's for app assigned ID's
	//These should only be used after database data has loaded
	int nextAvailableSongID;
	int nextAvailableRecordingID;
	int nextAvailableTrackID;
	//Data collections
	Songs songs;
	Recordings recordings;
	Tracks tracks;
	Users users;
	void initloadfromdb(char * sql,char *tablename);
	void executeQuery(char *sql);
    void executeCMDADD(Command cmd);
    void executeCMDDELETE(Command cmd);
    void executeCMDSHOW(Command cmd);

	void executeAddSong(Command cmd);
	void executeAddRecording(Command cmd);
	void executeAddTrack(Command cmd);
	void executeAddUser(Command cmd);
	void executeAddPlaylist(Command cmd);
	void executeAddPlaylistTrack(Command cmd);

	void executeDeleteRecording(Command cmd);
	void executeDeleteUser(Command cmd);
    void executeDeleteUserPlaylist(Command cmd);
    void executeDeleteUserPlaylistTrack(Command cmd);
	void executeDeleteTrack(Command cmd); //cascading delete
	void executeDeleteSong(Command cmd);

};
#endif
