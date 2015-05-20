/**
 * \file ssl_ticket.h
 *
 * \brief TLS server ticket callbacks implementation
 *
 *  Copyright (C) 2015, ARM Limited, All Rights Reserved
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef MBEDTLS_SSL_TICKET_H
#define MBEDTLS_SSL_TICKET_H

#include "ssl.h"
#include "aes.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief   Context for session ticket handling functions
 */
typedef struct
{
    unsigned char key_name[16];     /*!< name to quickly reject bad tickets */
    mbedtls_aes_context enc;        /*!< encryption context                 */
    mbedtls_aes_context dec;        /*!< decryption context                 */
    unsigned char mac_key[16];      /*!< authentication key                 */

    uint32_t ticket_lifetime;       /*!< lifetime of tickets in seconds     */

    /** Callback for getting (pseudo-)random numbers                        */
    int  (*f_rng)(void *, unsigned char *, size_t);
    void *p_rng;                    /*!< context for the RNG function       */
}
mbedtls_ssl_ticket_context;

/**
 * \brief           Initialize a ticket context.
 *                  (Just make it ready for mbedtls_ssl_ticket_setup()
 *                  or mbedtls_ssl_ticket_free().)
 *
 * \param ctx       Context to be initialized
 */
void mbedtls_ssl_ticket_init( mbedtls_ssl_ticket_context *ctx );

/**
 * \brief           Prepare context to be actually used
 *
 * \param ctx       Context to be set up
 * \param f_rng     RNG callback function
 * \param p_rng     RNG callback context
 * \param lifetime  Tickets lifetime in seconds
 *
 * \return          0 is successful,
 *                  or a specific MBEDTLS_ERR_XXX error code
 */
int mbedtls_ssl_ticket_setup( mbedtls_ssl_ticket_context *ctx,
    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
    uint32_t lifetime );

/**
 * \brief           Implementation of the ticket write callback
 *
 * \note            See \c mbedlts_ssl_ticket_write_t for description
 */
mbedtls_ssl_ticket_write_t mbedtls_ssl_ticket_write;

/**
 * \brief           Implementation of the ticket parse callback
 *
 * \note            See \c mbedlts_ssl_ticket_parse_t for description
 */
mbedtls_ssl_ticket_parse_t mbedtls_ssl_ticket_parse;

/**
 * \brief           Free a context's content and zeroize it.
 *
 * \param ctx       Context to be cleaned up
 */
void mbedtls_ssl_ticket_free( mbedtls_ssl_ticket_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* ssl_ticket.h */
