2 - Design reader - writer lock API

// Reader API - LOCK
/*
 * Lock fairness mutex
 * If any writer waiting, Unlock fairness_mutex return
 * Lock reader mutex
 * Increment reader_cnt
 * If first reader, lock writer mutex
 * Unlock reader mutex
 */
syserr_t
reader_lock(pthread_mutex_t *rd_mutex_p, pthread_mutex_t *wr_mutex_p)
{
Int ret_val = SYSERR_SUCCESS;
 If ((rd_mutex_p == NULL) || (wr_mutex_p == NULL)) {
  printf(“NULL parameter passed for argument\n”);
  return(SYSERR_NULL_PARAM);
 }

 ret_val = pthread_mutex_lock(rd_mutex_p);
 If (ret_val != SYSERR_SUCCESS) {
  printf(“Failed to lock rd_mutex_p, ret_val = ‘%d’\n”, ret_val);
  return(SYSERR_MUTEX_LOCK_ERR);
 }
 
 rd_cnt++;

If rd_cnt == 1, then lock wr_mutex
Unlock rd_mutex

}


// Reader API - UNLOCK
/*
 * Lock reader mutex
 * Decrement reader_cnt
 * If last reader, unlock writer mutex
 * Unlock reader mutex
 */
reader_unlock(pthread_mutex_t *rd_mutex_p, pthread_mutex_t *wr_mutex_p)
{
Int ret_val = SYSERR_SUCCESS;
 If ((rd_mutex_p == NULL) || (wr_mutex_p == NULL)) {
  printf(“NULL parameter passed for argument\n”);
  return(SYSERR_NULL_PARAM);
 }

 ret_val = pthread_mutex_lock(rd_mutex_p);
 If (ret_val != SYSERR_SUCCESS) {
  printf(“Failed to lock rd_mutex_p, ret_val = ‘%d’\n”, ret_val);
  return(SYSERR_MUTEX_LOCK_ERR);
 }
 
 rd_cnt–;

 If (rd_cnt == 0) {
 ret_val = pthread_mutex_unlock(wr_mutex_p);
 If (ret_val != SYSERR_SUCCESS) {
  printf(“Failed to unlock wr_mutex_p, ret_val = ‘%d’\n”, ret_val);
  return(SYSERR_MUTEX_UNLOCK_ERR);
 }

 ret_val = pthread_mutex_unlock(rd_mutex_p);
 If (ret_val != SYSERR_SUCCESS) {
  printf(“Failed to unlock rd_mutex_p, ret_val = ‘%d’\n”, ret_val);
  return(SYSERR_MUTEX_UNLOCK_ERR);
 }

 }


// Writer API - LOCK
/*
 * Signal about writer waiting
 * Lock writer mutex
 * Signal about writer acquired the lock
 */

// Writer API - UNLOCK
/*
 * Unlock writer mutex
 */

R R W R W W


