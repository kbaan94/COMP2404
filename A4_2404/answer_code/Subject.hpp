#include "playlist.h"
class Subject{
public:
	virtual void registerObserver(Observer* observer,Playlist *aPlayList)=0;
	virtual void removeObserver(Observer* observer,string aPlayList) = 0;
	virtual void notifyObservers() = 0;


};