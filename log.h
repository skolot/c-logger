/*
 * Copyright (c) 2012, Roman Dayneko <me@h0.org.ua> 
 *  
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without a written agreement
 * is hereby granted, provided that the above copyright notice and this
 * paragraph and the following two paragraphs appear in all copies.
 *  
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
 * LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
 * DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *  
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATIONS TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */


#ifndef __LOG_H__
#  define __LOG_H__

# include <errno.h>


# ifdef __USE_STDIO__
#  include <stdio.h>

#  define start_logging(ident) ((void)0)
#  define stop_logging() ((void)0)

    
#  ifndef __DEBUG__
#   define l_err(fmt,...)  fprintf(stderr, "+ERR:"fmt"\n", ##__VA_ARGS__)
#   define l_perr(str)     fprintf(stderr, "+ERR:%s: %s\n", str, strerror(errno))
#   define l_warn(fmt,...) fprintf(stderr, "+WARN:"fmt"\n", ##__VA_ARGS__)
#   define l_info(fmt,...) fprintf(stdout, "+INFO:"fmt"\n", ##__VA_ARGS__)
#  else /* __DEBUG__ */
#   define l_err(fmt,...)  fprintf(stderr, "+ERR:"__FILE__":%s:%d:"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#   define l_perr(str)     fprintf(stderr, "+ERR:"__FILE__":%s:%d: %s: %s\n",__FUNCTION__, __LINE__, str, strerror(errno))
#   define l_warn(fmt,...) fprintf(stderr, "+WARN:"__FILE__":%s:%d:"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#   define l_info(fmt,...) fprintf(stdout, "+INFO:" __FILE__":%s:%d:"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#  endif /* __DEBUG__ */
    
#  ifdef __DEBUG__
#   define l_debug(fmt,...) fprintf(stdout, "+DEBUG:", __FILE__":%s:%d:"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#  else 
#   define l_debug(fmt,...) ((void)0)
#  endif
    
# else /* __USE_STDIO__ */

/* by default using syslog */

#  include <syslog.h>
    
#  define start_logging(ident) openlog(ident, LOG_PID, LOG_DAEMON)
#  define stop_logging() closelog()
    
#  ifndef __DEBUG__
#   define l_err(fmt,...) syslog(LOG_ERR, fmt, ##__VA_ARGS__)
#   define l_perr(str) syslog(LOG_ERR, "%s: %s", str, strerror(errno))
#   define l_warn(fmt,...) syslog(LOG_WARNING, fmt, ##__VA_ARGS__)
#   define l_info(fmt,...) syslog(LOG_INFO, fmt, ##__VA_ARGS__)
#  else /* __DEBUG__ */
#   define l_err(fmt,...) syslog(LOG_ERR, __FILE__":%s:%d:"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#   define l_perr(str) syslog(LOG_ERR, __FILE__":%s:%d: %s: %s",__FUNCTION__, __LINE__, str, strerror(errno))
#   define l_warn(fmt,...) syslog(LOG_WARNING, __FILE__":%s:%d:"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#   define l_info(fmt,...) syslog(LOG_INFO, __FILE__":%s:%d:"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#  endif /* __DEBUG__ */
    
#  ifdef __DEBUG__
#   define l_debug(fmt,...) syslog(LOG_DEBUG, __FILE__":%s:%d:"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#  else 
#   define l_debug(fmt,...) ((void)0)
#  endif

# endif /* __USE_STDIO__ */

#endif /*__LOG_H__*/
