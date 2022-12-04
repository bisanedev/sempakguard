/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sempakguard.h"

#include "encode.h"
#include "decode.h"
#include "guard.h"

ZEND_DECLARE_MODULE_GLOBALS(sempakguard)


/* True global resources - no need for thread safety here */
static int le_sempakguard;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("sempakguard.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_sempakguard_globals, sempakguard_globals)
    STD_PHP_INI_ENTRY("sempakguard.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_sempakguard_globals, sempakguard_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_sempakguard_compiled(string arg)
   Return a string to confirm that the module is compiled in */

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(sempak_world)
{
    RETURN_STRING("Hentai Kamen world");
}

PHP_FUNCTION(sempak_run) {
    char * enc = NULL; /* encoded code */
    char * source = NULL;
    int enc_len;
    char * comp_name;
    char * eval_str; 
	 
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s"
            , &enc, &enc_len) == FAILURE) {
        return;
    }

    comp_name = zend_make_compiled_string_description("sempakguard" TSRMLS_CC);

    source = decode(enc, PRIVATE_KEY, PRIVATE_KEY_LEN);
	
    spprintf(&eval_str, 0, " ?>%s<?php ", source);
	
    free(source);

    if (zend_eval_string(eval_str, NULL, comp_name TSRMLS_CC) == FAILURE) {
        efree(comp_name);
        efree(eval_str);
        php_error_docref(NULL TSRMLS_CC, E_RECOVERABLE_ERROR, "Please make sure '<?php' end with '?>'", PHP_EOL);
        RETURN_FALSE;
    }

    efree(comp_name);
    efree(eval_str);
    RETURN_TRUE;
}

PHP_FUNCTION(sempak_encode) {
    char * code = NULL;
    int code_len = 0;
    char * ciphertext = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s"
            , &code, &code_len) == FAILURE) {
        return;
    }

    ciphertext = encode(code, code_len, PRIVATE_KEY, PRIVATE_KEY_LEN);

    //RETURN_STRING(ciphertext,1);
    RETURN_STRING(ciphertext);
}

/* {{{ php_sempakguard_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_sempakguard_init_globals(zend_sempakguard_globals *sempakguard_globals)
{
	sempakguard_globals->global_value = 0;
	sempakguard_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sempakguard)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sempakguard)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(sempakguard)
{
#if defined(COMPILE_DL_SEMPAKGUARD) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(sempakguard)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sempakguard)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sempakguard support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ sempakguard_functions[]
 *
 * Every user visible function must have an entry in sempakguard_functions[].
 */
const zend_function_entry sempakguard_functions[] = {	
	PHP_FE(sempak_world, NULL)
	PHP_FE(sempak_run, NULL)
    PHP_FE(sempak_encode, NULL) {NULL, NULL, NULL}
	//PHP_FE_END	
};
/* }}} */

/* {{{ sempakguard_module_entry
 */
zend_module_entry sempakguard_module_entry = {
	STANDARD_MODULE_HEADER,
	"sempakguard",
	sempakguard_functions,
	PHP_MINIT(sempakguard),
	PHP_MSHUTDOWN(sempakguard),
	PHP_RINIT(sempakguard),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(sempakguard),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(sempakguard),
	PHP_SEMPAKGUARD_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SEMPAKGUARD
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(sempakguard)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
