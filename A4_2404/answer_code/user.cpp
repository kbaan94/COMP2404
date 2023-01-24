/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */


#include <iostream>
#include <string>
using namespace std;

#include "user.h"
#include "track.h"

int User::nextUserNumericID = 1000;

User::User(const string & aUserID, const string & aName){
	cout << "User(string&, string&, int)" << endl;
	userid = aUserID;
	name = aName;
	id = nextUserNumericID++;
}
User::User(const User & aUser){
	cout << "User(const User & aUser)" << endl;
	cout << "ERROR: User(const User & aUser) --should never run" << endl;
}
User::~User(){
	cout << "~User(void)" << endl;
	//user objects own playlists
	for(int i=0; i<playlists.size(); i++)
		delete playlists[i]; //delete playlists this user owns

}
int User::getID(){return id;}

string User::getUserID(){return userid;}

vector<Playlist*>::iterator User::findPosition(Playlist & aPlaylist){
	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr)
		if(*itr == &aPlaylist) return itr;
	return playlists.end();
}

Playlist* User::findPlaylist(const string & aPlaylistName){
	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr)
		if(((*itr)->getName()).compare(aPlaylistName) == 0) return *itr;
	return NULL;
}
void User::addPlaylist(Playlist & aPlaylist){
	//add playlist if it does not already exist
	vector<Playlist*>::iterator itr = findPosition(aPlaylist);
	if(itr == playlists.end()) {
		playlists.push_back(&aPlaylist);
	}
}

void User::removePlaylist(Playlist & aPlaylist){
	vector<Playlist*>::iterator itr = findPosition(aPlaylist);
	if(itr != playlists.end()) {
	   Playlist * playlist = *itr;
	   playlists.erase(itr);
	   delete playlist;
	}

	//if a playlist gets deleted it gets removed in the follower list as well
	int i=0;
	vector<int> indexToDelete;
	for(auto observer:playlist_observers){
		if(observer.first->getName()==aPlaylist.getName()){
			indexToDelete.push_back(i);

		}
		i++;
	}
	// remove from observers list
	for(auto x: indexToDelete){
		playlist_observers.erase(playlist_observers.begin()+x);
	}
}

void User::removeTrack(Track & aTrack){
	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr){
		Playlist * playlist = *itr;
		playlist->removeTrack(aTrack);
	}
	this->notifyObservers();
}
string User::toString()const {
	string indent = "     ";
	string s;
	s.append(userid + " " + name);
	s.append("\n");
	s.append(indent + "Playlists:\n");
	for (vector<Playlist*>::size_type i = 0 ; i < playlists.size(); i++){
		   s.append(indent + to_string(i) + " " + (playlists[i])->toString() + "\n");
		   s.append("\n");
	}

	return s;
}
void User::registerObserver(Observer* observer,Playlist *aPlayList){
	
	if(aPlayList==NULL){
		return;
	}

	playlist_observers.push_back(make_pair(aPlayList,observer));

}
void User::removeObserver(Observer* obs,string aPlayList) {
	
	
	vector<int> indexToDelete;
	int i=0;
	for(auto observer:playlist_observers){
		if(observer.first->getName()==aPlayList && observer.second==obs){
			indexToDelete.push_back(i);
		}
		i++;
	}
	for(auto x: indexToDelete){
		playlist_observers.erase(playlist_observers.begin()+x);
	}
}

void User::notifyObservers(){

	for(auto observer:playlist_observers){
		observer.second->update(observer.first);
	}
}
	
void User::update(Playlist *aPlayList){

	Playlist *playlist;
	if(aPlayList==NULL){
		return;
	}
	vector<Track*> &updatedTrack = aPlayList->getTracks(); 

	if(this->findPlaylist(aPlayList->getName())!=NULL){
		//already registered with the playlist
		playlist =  this->findPlaylist(aPlayList->getName());
	}else{
		playlist = new Playlist(aPlayList->getName());
		this->addPlaylist(*playlist);
	}
	vector<Track*> currTrack = playlist->getTracks();
	int oldSize = currTrack.size();
	for(auto track:currTrack){
			if(find(updatedTrack.begin(),updatedTrack.end(),track)==updatedTrack.end()){
				playlist->removeTrack(*track);
			}
	} 
	
	for(auto track:updatedTrack){
		playlist->addTrack(*track);
	}
	int newSize = playlist->getTracks().size();
	
	if(newSize!=oldSize){
		notifyObservers();
	}


}

ostream & operator<<(ostream & out, const User & aUser){
	out << aUser.toString() << endl;
	return out;
}

