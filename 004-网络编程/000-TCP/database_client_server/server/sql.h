void is_sqlite(int rc);  //�������ݿ�
void is_malloc_ok(vpChat *list);
void is_sqlite_ok(int rc);
void open_db(sqlite3 **db);//�����ݿ�
void creat_user_db(sqlite3 *db,char **errmsg);//����user���ݱ�
void creat_data_db(sqlite3 *db,char **errmsg);//����data���ݱ�
void creat_online_db(sqlite3 *db,char **errmsg);//����online���ݱ�
void creat_server_db(sqlite3 *db,char **errmsg);//����server���ݱ�
void insert_server_db(sqlite3 *db,char *time,char **errmsg);//�server�������
void read_db_ok(sqlite3 *db,char *errmsg,char*tablename);//�������
void delete_clean_db(sqlite3 *db,char *tablename,char **errmsg);
int read_online_fd(sqlite3 *db,char **errmsg,char *user);//������
int read_online_flag(sqlite3 *db,char **errmsg,char *user);//������
void write_online_all(sqlite3 *db,char **errmsg,vpChat temp);
int update_passwd(sqlite3 *db,char **errmsg,char *name,char *passwd);
void insert_data_db(sqlite3 *db,char **errmsg,char *time,vpChat temp);
int update_flag(sqlite3 *db,char **errmsg,char *name,int flag);
int delete_user(sqlite3 *db,char **errmsg,char *name);
void read_online_all(sqlite3 *db,char **errmsg,vpChat temp);//���������
void read_data(sqlite3 *db,char **errmsg,vpChat temp);//���������
int update_user(sqlite3 *db,char **errmsg,char *name,char *toname);//����
int update_db_data(sqlite3 *db,char **errmsg,char *name,char *toname);//����
