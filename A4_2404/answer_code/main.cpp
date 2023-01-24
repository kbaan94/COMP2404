/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                     */
/*  DISCLAIMER                                         */
/*  This is "Early Course" code and does not use       */
/*  many c++ features that might be appropriate        */
/*  For example:                                       */
/*  -No inheritance is used yet                        */
/*  -Many items are passed by value resulting in copies*/
/*  -Many items are not const protected that should be */
/*  -There is no dynamic memory allocation yet         */
/*  -No base-member initialization yet                 */
/*                                                     */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "mytunes.h"

int main()
{
  MyTunes app;
  app.run();
  return 0;
}
