/* neatvi main header */

/* helper macros */
#define LEN(a)		(sizeof(a) / sizeof((a)[0]))
#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) < (b) ? (b) : (a))

/* line buffer, managing a number of lines */
struct lbuf *lbuf_make(void);
void lbuf_free(struct lbuf *lbuf);
int lbuf_rd(struct lbuf *lbuf, int fd, int beg, int end);
int lbuf_wr(struct lbuf *lbuf, int fd, int beg, int end);
void lbuf_edit(struct lbuf *lbuf, const char *s, int beg, int end);
char *lbuf_cp(struct lbuf *lbuf, int beg, int end);
char *lbuf_get(struct lbuf *lbuf, int pos);
int lbuf_len(struct lbuf *lbuf);
void lbuf_mark(struct lbuf *lbuf, int mark, int pos, int off);
int lbuf_jump(struct lbuf *lbuf, int mark, int *pos, int *off);
int lbuf_undo(struct lbuf *lbuf);
int lbuf_redo(struct lbuf *lbuf);
int lbuf_modified(struct lbuf *lb);
void lbuf_saved(struct lbuf *lb, int clear);
int lbuf_indents(struct lbuf *lb, int r);
int lbuf_eol(struct lbuf *lb, int r);
void lbuf_globset(struct lbuf *lb, int pos, int dep);
int lbuf_globget(struct lbuf *lb, int pos, int dep);
/* motions */
int lbuf_findchar(struct lbuf *lb, const char *cs, int cmd, int n, int *r, int *o);
int lbuf_search(struct lbuf *lb, char *kw, int dir, int *r, int *o, int *len);
int lbuf_paragraphbeg(struct lbuf *lb, int dir, int *row, int *off);
int lbuf_sectionbeg(struct lbuf *lb, int dir, const char *sec, int *row, int *off);
int lbuf_wordbeg(struct lbuf *lb, int big, int dir, int *row, int *off);
int lbuf_wordend(struct lbuf *lb, int big, int dir, int *row, int *off);
int lbuf_pair(struct lbuf *lb, int *row, int *off);

/* string buffer, variable-sized string */
struct sbuf *sbuf_make(void);
void sbuf_free(struct sbuf *sb);
char *sbuf_done(struct sbuf *sb);
char *sbuf_buf(struct sbuf *sb);
void sbuf_chr(struct sbuf *sb, int c);
void sbuf_str(struct sbuf *sb, const char *s);
void sbuf_mem(struct sbuf *sb, const char *s, int len);
void sbuf_printf(struct sbuf *sbuf, char *s, ...);
int sbuf_len(struct sbuf *sb);
void sbuf_cut(struct sbuf *s, int len);

/* regular expressions */
#define RE_ICASE		1
#define RE_NOTBOL		2
#define RE_NOTEOL		4
/* regular expression sets: searching for multiple regular expressions */
struct rset *rset_make(int n, const char **pat, int flg);
int rset_find(struct rset *re, const char *s, int n, int *grps, int flg);
void rset_free(struct rset *re);
char *re_read(const char **src);
/* searching for a single pattern regular expression */
struct rstr *rstr_make(const char *re, int flg);
int rstr_find(struct rstr *rs, char *s, int n, int *grps, int flg);
void rstr_free(struct rstr *rs);

/* rendering lines */
int *ren_position(const char *s);
int ren_next(char *s, int p, int dir);
int ren_eol(char *s, int dir);
int ren_pos(char *s, int off);
int ren_cursor(char *s, int pos);
int ren_noeol(const char *s, int p);
int ren_off(char *s, int pos);
int ren_wid(char *s);
int ren_region(char *s, int c1, int c2, int *l1, int *l2, int closed);
const char *ren_translate(const char *s, const char *ln);
int ren_cwid(const char *s, int pos);

/* text direction */
int dir_context(const char *s);
void dir_reorder(const char *s, int *ord);
void dir_init(void);
void dir_done(void);

/* string registers */
char *reg_get(int c, int *lnmode);
void reg_put(int c, const char *s, int lnmode);
void reg_done(void);

/* utf-8 helper functions */
int uc_len(const char *s);
int uc_wid(const char *s);
int uc_slen(const char *s);
int uc_code(const char *s);
const char *uc_chr(const char *s, int off);
int uc_off(const char *s, int off);
char *uc_sub(const char *s, int beg, int end);
char *uc_dup(const char *s);
char *uc_cat(const char *s, const char *r);
int uc_isspace(const char *s);
int uc_isprint(const char *s);
int uc_isdigit(const char *s);
int uc_isalpha(const char *s);
int uc_kind(const char *c);
int uc_isbell(const char *c);
int uc_iscomb(const char *c);
const char **uc_chop(const char *s, int *n);
const char *uc_next(const char *s);
const char *uc_prev(const char *beg, const char *s);
const char *uc_beg(const char *beg, const char *s);
const char *uc_end(const char *s);
const char *uc_shape(const char *beg, const char *s);
const char *uc_lastline(const char *s);

/* managing the terminal */
#define xrows		(term_rows())
#define xcols		(term_cols())

void term_init(void);
void term_done(void);
void term_suspend(void);
void term_str(const char *s);
void term_chr(int ch);
void term_pos(int r, int c);
void term_clear(void);
void term_kill(void);
void term_room(int n);
void term_window(int row, int cnt);
int term_rows(void);
int term_cols(void);
int term_rowx(void);
int term_read(void);
void term_record(void);
void term_commit(void);
const char *term_seqattr(int att, int old);
const char *term_seqkill(void);
void term_push(char *s, int n);
char *term_cmd(int *n);

#define TK_CTL(x)	((x) & 037)
#define TK_INT(c)	((c) < 0 || (c) == TK_ESC || (c) == TK_CTL('c'))
#define TK_ESC		(TK_CTL('['))

/* line-oriented input and output */
char *led_prompt(const char *pref, const char *post, int *kmap, const char *syn, char *hist);
char *led_input(char *pref, char *post, int *left, int *kmap, const char *syn, void (*nextline)(void), void (*showinfo)(char *ln));
void led_print(const char *msg, int row, int left, const char *syn);
void led_printmsg(const char *s, int row, const char *syn);
const char *led_read(int *kmap);

/* ex commands */
void ex(void);
int ex_command(const char *cmd);
char *ex_read(const char *msg);
void ex_print(const char *line);
void ex_show(const char *msg);
int ex_init(char **files);
void ex_done(void);
char *ex_path(void);
char *ex_filetype(void);
struct lbuf *ex_lbuf(void);
int ex_kwd(char **kwd, int *dir);
void ex_kwdset(const char *kwd, int dir);
int ex_list(char **ls, int size);

#define EXLEN	512		/* ex line length */
#define xb 	ex_lbuf()

/* process management */
char *cmd_pipe(const char *cmd, char *s, int oproc);
int cmd_exec(const char *cmd);

/* syntax highlighting */
#define SYN_BD		0x010000
#define SYN_IT		0x020000
#define SYN_RV		0x040000
#define SYN_FGMK(f)	(0x100000 | (f))
#define SYN_BGMK(b)	(0x200000 | ((b) << 8))

#define SYN_FLG		0xff0000
#define SYN_FGSET(a)	((a) & 0x1000ff)
#define SYN_BGSET(a)	((a) & 0x20ff00)
#define SYN_FG(a)	((a) & 0xff)
#define SYN_BG(a)	(((a) >> 8) & 0xff)

int *syn_highlight(const char *ft, const char *s);
const char *syn_filetype(const char *path);
void syn_context(int att);
int syn_merge(int old, int new);
void syn_init(void);
void syn_done(void);

/* configuration variables */
int conf_dirmark(int idx, const char **pat, int *ctx, int *dir, int *grp);
int conf_dircontext(int idx, const char **pat, int *ctx);
int conf_placeholder(int idx, const char **s, const char **d, int *wid);
int conf_highlight(int idx, const char **ft, int **att, const char **pat, int *end);
int conf_filetype(int idx, const char **ft, const char **pat);
int conf_hlrev(void);
int conf_hlline(void);
int conf_hlmode(void);
int conf_hlback(void);
int conf_mode(void);
const char **conf_kmap(int id);
int conf_kmapfind(const char *name);
const char *conf_digraph(int c1, int c2);
const char *conf_lnpref(void);
const char *conf_definition(char *ft);
const char *conf_section(char *ft);
const char *conf_ecmd(void);

/* global variables */
extern int xrow;
extern int xoff;
extern int xtop;
extern int xleft;
extern int xvis;
extern int xled;
extern int xquit;
extern int xic;
extern int xai;
extern int xtd;
extern int xshape;
extern int xorder;
extern int xhl;
extern int xhll;
extern int xkmap;
extern int xkmap_alt;
extern int xlim;
extern int xru;
extern int xhist;

/* tag file handling */
int tag_init(void);
int tag_find(const char *name, int *pos, int dir, char *path, int pathlen, char *cmd, int cmdlen);
void tag_done(void);
