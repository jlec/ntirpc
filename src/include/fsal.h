/*
 *
 *
 * Copyright CEA/DAM/DIF  (2008)
 * contributeur : Philippe DENIEL   philippe.deniel@cea.fr
 *                Thomas LEIBOVICI  thomas.leibovici@cea.fr
 *
 *
 * Ce logiciel est un serveur implementant le protocole NFS.
 *
 * Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
 * respectant les principes de diffusion des logiciels libres. Vous pouvez
 * utiliser, modifier et/ou redistribuer ce programme sous les conditions
 * de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA
 * sur le site "http://www.cecill.info".
 *
 * En contrepartie de l'accessibilit� au code source et des droits de copie,
 * de modification et de redistribution accord�s par cette licence, il n'est
 * offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
 * seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
 * titulaire des droits patrimoniaux et les conc�dants successifs.
 *
 * A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
 * associ�s au chargement,  � l'utilisation,  � la modification et/ou au
 * d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
 * donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
 * manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
 * avertis poss�dant  des  connaissances  informatiques approfondies.  Les
 * utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
 * logiciel � leurs besoins dans des conditions permettant d'assurer la
 * s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
 * � l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.
 *
 * Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
 * pris connaissance de la licence CeCILL, et que vous en avez accept� les
 * termes.
 *
 * ---------------------
 *
 * Copyright CEA/DAM/DIF (2005)
 *  Contributor: Philippe DENIEL  philippe.deniel@cea.fr
 *               Thomas LEIBOVICI thomas.leibovici@cea.fr
 *
 *
 * This software is a server that implements the NFS protocol.
 * 
 *
 * This software is governed by the CeCILL  license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 * ---------------------------------------
 */

/**
 * \file    fsal.h
 * \author  $Author: leibovic $
 * \date    $Date: 2006/02/17 13:41:01 $
 * \version $Revision: 1.72 $
 * \brief   File System Abstraction Layer interface.
 *
 *
 */

#ifndef _FSAL_H
#define _FSAL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef _SOLARIS
#include "solaris_port.h"
#endif /* _SOLARIS */

/* fsal_types contains constants and type definitions for FSAL */
#include "fsal_types.h"
#include "common_utils.h"

#ifndef _USE_SWIG
/******************************************************
 *            Attribute mask management.
 ******************************************************/


/** this macro tests if an attribute is set
 *  example :
 *  FSAL_TEST_MASK( attrib_list.supported_attributes, FSAL_ATTR_CREATION )
 */
#define FSAL_TEST_MASK( _attrib_mask_ , _attr_const_ ) \
                      ( (_attrib_mask_) & (_attr_const_) )


/** this macro sets an attribute
 *  example :
 *  FSAL_SET_MASK( attrib_list.asked_attributes, FSAL_ATTR_CREATION )
 */
#define FSAL_SET_MASK( _attrib_mask_ , _attr_const_ ) \
                    ( (_attrib_mask_) |= (_attr_const_) )


/** this macro clears the attribute mask
 *  example :
 *  FSAL_CLEAR_MASK( attrib_list.asked_attributes )
 */
#define FSAL_CLEAR_MASK( _attrib_mask_ ) \
                    ( (_attrib_mask_) = 0LL )



/******************************************************
 *              Initialization tools.
 ******************************************************/


/** This macro initializes init info behaviors and values.
 *  Examples :
 *  FSAL_SET_INIT_INFO( parameter.fs_common_info ,
 *                      maxfilesize              ,
 *                      FSAL_INIT_MAX_LIMIT      ,
 *                      0x00000000FFFFFFFFLL    );
 *
 *  FSAL_SET_INIT_INFO( parameter.fs_common_info ,
 *                      linksupport              ,
 *                      FSAL_INIT_FORCEVALUE     ,
 *                      FALSE                   );
 *
 */
          
#define FSAL_SET_INIT_INFO( _common_info_struct_ , _field_name_ ,   \
                                    _field_behavior_ , _value_ ) do \
           {                                                        \
             _common_info_struct_.behaviors._field_name_ = _field_behavior_ ;\
             if ( _field_behavior_ != FSAL_INIT_FS_DEFAULT )        \
               _common_info_struct_.values._field_name_ = _value_ ; \
           } while (0)



/** This macro initializes the behavior for one parameter
 *  to default filesystem value.
 *  Examples :
 *  FSAL_SET_INIT_DEFAULT( parameter.fs_common_info , case_insensitive );
 */
#define FSAL_SET_INIT_DEFAULT( _common_info_struct_ , _field_name_ ) \
        do {                                                         \
             _common_info_struct_.behaviors._field_name_             \
                = FSAL_INIT_FS_DEFAULT ;                             \
           } while (0)



/**
 * Those routines set the default parameters
 * for FSAL init structure.
 * \return ERR_FSAL_NO_ERROR (no error) ,
 *         ERR_FSAL_FAULT (null pointer given as parameter),
 *         ERR_FSAL_SERVERFAULT (unexpected error)
 */
fsal_status_t  FSAL_SetDefault_FSAL_parameter(
                             fsal_parameter_t *  out_parameter );     

fsal_status_t  FSAL_SetDefault_FS_common_parameter(
                             fsal_parameter_t *  out_parameter );

fsal_status_t  FSAL_SetDefault_FS_specific_parameter(
                             fsal_parameter_t *  out_parameter );

/**
 * FSAL_load_FSAL_parameter_from_conf,
 * FSAL_load_FS_common_parameter_from_conf,
 * FSAL_load_FS_specific_parameter_from_conf:
 *
 * Those functions initialize the FSAL init parameter
 * structure from a configuration structure.
 *
 * \param in_config (input):
 *        Structure that represents the parsed configuration file.
 * \param out_parameter (ouput)
 *        FSAL initialization structure filled according
 *        to the configuration file given as parameter.
 *
 * \return ERR_FSAL_NO_ERROR (no error) ,
 *         ERR_FSAL_NOENT (missing a mandatory stanza in config file),
 *         ERR_FSAL_INVAL (invalid parameter),
 *         ERR_FSAL_SERVERFAULT (unexpected error)
 *         ERR_FSAL_FAULT (null pointer given as parameter),
 */
fsal_status_t  FSAL_load_FSAL_parameter_from_conf(
      config_file_t       in_config,
      fsal_parameter_t *  out_parameter
    );

fsal_status_t  FSAL_load_FS_common_parameter_from_conf(
      config_file_t       in_config,
      fsal_parameter_t *  out_parameter
    );
fsal_status_t  FSAL_load_FS_specific_parameter_from_conf(
      config_file_t       in_config,
      fsal_parameter_t *  out_parameter
    );




/** 
 *  FSAL_Init:
 *  Initializes Filesystem abstraction layer.
 */
fsal_status_t  FSAL_Init(
    fsal_parameter_t        * init_info         /* IN */
);


          
/******************************************************
 *              FSAL Errors handling.
 ******************************************************/
        

/** Tests whether the returned status is errorneous.
 *  Example :
 *  if ( FSAL_IS_ERROR( status = FSAL_call(...) )){
 *     printf("ERROR status = %d, %d\n", status.major,status.minor);
 *  }
 */
#define FSAL_IS_ERROR( _status_ ) \
        ( ! ( ( _status_ ).major == ERR_FSAL_NO_ERROR ) )

     
/**
 *  Tests whether an error code is retryable.
 */
fsal_boolean_t  fsal_is_retryable( fsal_status_t  status );
          
#endif /* ! _USE_SWIG */


/******************************************************
 *              FSAL Strings handling.
 ******************************************************/


fsal_status_t FSAL_str2name(
      const char     * string ,        /* IN */
      fsal_mdsize_t  in_str_maxlen ,   /* IN */
      fsal_name_t    * name            /* OUT */
    );


fsal_status_t FSAL_name2str(
      fsal_name_t * p_name,             /* IN */
      char        * string ,          /* OUT */
      fsal_mdsize_t  out_str_maxlen   /* IN */
    );


int FSAL_namecmp( fsal_name_t * p_name1, fsal_name_t * p_name2 );


fsal_status_t FSAL_namecpy( fsal_name_t * p_tgt_name, fsal_name_t * p_src_name );


fsal_status_t FSAL_str2path(
      char           * string ,        /* IN */
      fsal_mdsize_t  in_str_maxlen ,   /* IN */
      fsal_path_t    * p_path          /* OUT */
    );


fsal_status_t FSAL_path2str(
      fsal_path_t * p_path,           /* IN */
      char        * string ,          /* OUT */
      fsal_mdsize_t  out_str_maxlen   /* IN */
    );


int FSAL_pathcmp( fsal_path_t * p_path1, fsal_path_t * p_path2 );


fsal_status_t FSAL_pathcpy( fsal_path_t * p_tgt_path, fsal_path_t * p_src_path );

#ifndef _USE_SWIG
/** utf8 management functions. */

fsal_status_t FSAL_buffdesc2name(fsal_buffdesc_t * in_buf,fsal_name_t * out_name);

fsal_status_t FSAL_buffdesc2path(fsal_buffdesc_t * in_buf,fsal_path_t * out_path);

fsal_status_t FSAL_path2buffdesc(fsal_path_t * in_path, fsal_buffdesc_t * out_buff);

fsal_status_t FSAL_name2buffdesc(fsal_name_t * in_name, fsal_buffdesc_t * out_buff);

#endif /* ! _USE_SWIG */

/* snprintmem and sscanmem are defined into common_utils */

#define snprintHandle(target, tgt_size, p_handle) \
  snprintmem(target,tgt_size,(caddr_t)p_handle,sizeof(fsal_handle_t))

#define snprintCookie(target, tgt_size, p_cookie) \
  snprintmem(target,tgt_size,(caddr_t)p_cookie,sizeof(fsal_cookie_t))

#define snprintAttrs(target, tgt_size, p_attrs) \
  snprintmem(target,tgt_size,(caddr_t)p_attrs,sizeof(fsal_attrib_list_t))

#define sscanHandle(p_handle,str_source) \
  sscanmem( (caddr_t)p_handle,sizeof(fsal_handle_t),str_source )

#define sscanCookie(p_cookie,str_source) \
  sscanmem( (caddr_t)p_cookie,sizeof(fsal_cookie_t),str_source )

#define sscanAttrs(p_attrs,str_source) \
  sscanmem( (caddr_t)p_attrs,sizeof(fsal_attrib_list_t),str_source )


     
/******************************************************
 *              FSAL handles management.
 ******************************************************/
     

/** Compare 2 handles.
 *  \return - 0 if handle are the same
 *          - A non null value else.
 */
int FSAL_handlecmp( fsal_handle_t * handle1, fsal_handle_t * handle2, fsal_status_t * status);


#ifndef _USE_SWIG

/**
 * FSAL_Handle_to_HashIndex
 * This function is used for hashing a FSAL handle
 * in order to dispatch entries into the hash table array.
 *
 * \param p_handle	The handle to be hashed
 * \param cookie 	Makes it possible to have different hash value for the
 *			same handle, when cookie changes.
 * \param alphabet_len	Parameter for polynomial hashing algorithm
 * \param index_size	The range of hash value will be [0..index_size-1]
 *
 * \return The hash value
 */

unsigned int FSAL_Handle_to_HashIndex( fsal_handle_t * p_handle,
			      	    unsigned int cookie,
			      	    unsigned int alphabet_len,
			      	    unsigned int index_size);


/*
 * FSAL_Handle_to_RBTIndex 
 * This function is used for generating a RBT node ID 
 * in order to identify entries into the RBT.
 *
 * \param p_handle	The handle to be hashed
 * \param cookie 	Makes it possible to have different hash value for the
 *			same handle, when cookie changes.
 *
 * \return The hash value
 */

unsigned int FSAL_Handle_to_RBTIndex( fsal_handle_t * p_handle, unsigned int cookie );



/** FSAL_DigestHandle :
 *  convert an fsal_handle_t to a buffer
 *  to be included into NFS handles,
 *  or another digest.
 */
fsal_status_t FSAL_DigestHandle(
    fsal_export_context_t  * p_expcontext,      /* IN */
    fsal_digesttype_t       output_type,        /* IN */
    fsal_handle_t         * in_fsal_handle,     /* IN */
    caddr_t                 out_buff            /* OUT */
);


/** FSAL_ExpandHandle :
 *  convert a buffer extracted from NFS handles
 *  to an FSAL handle.
 */
fsal_status_t FSAL_ExpandHandle(
    fsal_export_context_t  * p_expcontext,    /* IN */
    fsal_digesttype_t        in_type,         /* IN */
    caddr_t                  in_buff,         /* IN */
    fsal_handle_t          * out_fsal_handle  /* OUT */
);


/**
 *  FSAL_CleanObjectResources:
 *  Garbages the resources relative to an fsal_handle_t.
 */
fsal_status_t FSAL_CleanObjectResources( fsal_handle_t * in_fsal_handle ); /* IN */


/******************************************************
 *              FSAL context management.
 ******************************************************/

fsal_status_t FSAL_BuildExportContext(
        fsal_export_context_t   * p_export_context,    /* OUT */
        fsal_path_t             * p_export_path,       /* IN */
        char                    * fs_specific_options  /* IN */
      );


fsal_status_t FSAL_InitClientContext(
        fsal_op_context_t       * p_thr_context      /* OUT  */
      );

fsal_status_t FSAL_GetClientContext(
        fsal_op_context_t       * p_thr_context,      /* IN/OUT  */
        fsal_export_context_t   * p_export_context,   /* IN */    
        fsal_uid_t              uid,                  /* IN */
        fsal_gid_t              gid,                  /* IN */
        fsal_gid_t              * alt_groups,         /* IN */
        fsal_count_t            nb_alt_groups         /* IN */
      );

#endif /* ! _USE_SWIG */



/******************************************************
 *              Common Filesystem calls.
 ******************************************************/


fsal_status_t FSAL_lookup (
    fsal_handle_t         * parent_directory_handle,        /* IN */
    fsal_name_t           * p_filename,                     /* IN */
    fsal_op_context_t     * p_context,                      /* IN */
    fsal_handle_t         * object_handle,                  /* OUT */
    fsal_attrib_list_t    * object_attributes               /* [ IN/OUT ] */
);


fsal_status_t FSAL_lookupPath (
    fsal_path_t           * p_path,            /* IN */
    fsal_op_context_t     * p_context,         /* IN */
    fsal_handle_t         * object_handle,     /* OUT */
    fsal_attrib_list_t    * object_attributes  /* [ IN/OUT ] */
);


fsal_status_t FSAL_lookupJunction (
    fsal_handle_t         * p_junction_handle,   /* IN */
    fsal_op_context_t     * p_context,           /* IN */
    fsal_handle_t         * p_fsoot_handle,      /* OUT */
    fsal_attrib_list_t    * p_fsroot_attributes  /* [ IN/OUT ] */
);


fsal_status_t FSAL_access(
    fsal_handle_t              * object_handle,      /* IN */
    fsal_op_context_t          * p_context,          /* IN */
    fsal_accessflags_t         access_type,          /* IN */
    fsal_attrib_list_t         * object_attributes   /* [ IN/OUT ] */
);

/**
 * FSAL_test_access :
 * test if a client identified by cred can access the object
 * whom the attributes are object_attributes.
 * The following fields of the object_attributes structure MUST be filled :
 * acls (if supported), mode, owner, group.
 * This doesn't make any call to the filesystem,
 * as a result, this doesn't ensure that the file exists, nor that
 * the permissions given as parameters are the actual file permissions :
 * this must be ensured by the cache_inode layer, using FSAL_getattrs,
 * for example.
 */
fsal_status_t FSAL_test_access(
    fsal_op_context_t          * p_context,          /* IN */
    fsal_accessflags_t           access_type,        /* IN */
    fsal_attrib_list_t         * object_attributes   /* IN */
);

fsal_status_t FSAL_create(
    fsal_handle_t         * parent_directory_handle, /* IN */
    fsal_name_t           * p_filename,              /* IN */
    fsal_op_context_t     * p_context,               /* IN */
    fsal_accessmode_t       accessmode,              /* IN */
    fsal_handle_t         * object_handle,           /* OUT */
    fsal_attrib_list_t    * object_attributes        /* [ IN/OUT ] */
);

fsal_status_t FSAL_mkdir(
    fsal_handle_t         * parent_directory_handle, /* IN */
    fsal_name_t           * p_dirname,               /* IN */
    fsal_op_context_t     * p_context,               /* IN */
    fsal_accessmode_t       accessmode,              /* IN */
    fsal_handle_t         * object_handle,           /* OUT */
    fsal_attrib_list_t    * object_attributes        /* [ IN/OUT ] */
);

fsal_status_t FSAL_truncate(
    fsal_handle_t         * filehandle,              /* IN */
    fsal_op_context_t     * p_context,               /* IN */
    fsal_size_t             length,                  /* IN */
    fsal_file_t           * file_descriptor,         /* INOUT */
    fsal_attrib_list_t    * object_attributes        /* [ IN/OUT ] */
);

fsal_status_t FSAL_getattrs(
    fsal_handle_t         * filehandle,              /* IN */
    fsal_op_context_t     * p_context,               /* IN */
    fsal_attrib_list_t    * object_attributes        /* IN/OUT */
);

fsal_status_t FSAL_setattrs(
    fsal_handle_t         * filehandle,        /* IN */
    fsal_op_context_t     * p_context,         /* IN */
    fsal_attrib_list_t    * attrib_set,        /* IN */
    fsal_attrib_list_t    * object_attributes  /* [ IN/OUT ] */
);

fsal_status_t FSAL_link(
    fsal_handle_t         * target_handle,     /* IN */
    fsal_handle_t         * dir_handle,        /* IN */
    fsal_name_t           * p_link_name,       /* IN */
    fsal_op_context_t     * p_context,         /* IN */
    fsal_attrib_list_t    * attributes         /* [ IN/OUT ] */
);

fsal_status_t FSAL_opendir(
    fsal_handle_t             * dir_handle,           /* IN */
    fsal_op_context_t         * p_context,            /* IN */
    fsal_dir_t                * dir_descriptor,       /* OUT */
    fsal_attrib_list_t        * dir_attributes        /* [ IN/OUT ] */
);

fsal_status_t FSAL_readdir(
    fsal_dir_t            * dir_descriptor,     /* IN */
    fsal_cookie_t         start_position ,      /* IN */
    fsal_attrib_mask_t    get_attr_mask,        /* IN */
    fsal_mdsize_t         buffersize,           /* IN */
    fsal_dirent_t         * pdirent,            /* OUT */
    fsal_cookie_t         * end_position,       /* OUT */
    fsal_count_t          * nb_entries,         /* OUT */
    fsal_boolean_t        * end_of_dir          /* OUT */
);


fsal_status_t FSAL_closedir(
    fsal_dir_t * dir_descriptor         /* IN */
);

fsal_status_t FSAL_open(
    fsal_handle_t         * filehandle,             /* IN */
    fsal_op_context_t     * p_context,              /* IN */
    fsal_openflags_t      openflags,                /* IN */
    fsal_file_t           * file_descriptor,        /* OUT */
    fsal_attrib_list_t    * file_attributes         /* [ IN/OUT ] */
);

fsal_status_t FSAL_open_by_name(
    fsal_handle_t         * dirhandle,             /* IN */
    fsal_name_t           * filename,              /* IN */
    fsal_op_context_t     * p_context,              /* IN */
    fsal_openflags_t        openflags,              /* IN */
    fsal_file_t           * file_descriptor,        /* OUT */
    fsal_attrib_list_t    * file_attributes         /* [ IN/OUT ] */) ;

fsal_status_t FSAL_open_by_fileid(
    fsal_handle_t         * filehandle,             /* IN */
    fsal_u64_t              fileid,                 /* IN */
    fsal_op_context_t     * p_context,              /* IN */
    fsal_openflags_t        openflags,              /* IN */
    fsal_file_t           * file_descriptor,        /* OUT */
    fsal_attrib_list_t    * file_attributes         /* [ IN/OUT ] */ ) ;

fsal_status_t FSAL_read(
    fsal_file_t           * file_descriptor,         /*  IN  */
    fsal_seek_t           * seek_descriptor,         /* [IN] */
    fsal_size_t             buffer_size,             /*  IN  */
    caddr_t                 buffer,                  /* OUT  */
    fsal_size_t           * read_amount,             /* OUT  */
    fsal_boolean_t        * end_of_file              /* OUT  */
);

fsal_status_t FSAL_write(
    fsal_file_t        * file_descriptor,     /* IN */
    fsal_seek_t        * seek_descriptor,     /* IN */
    fsal_size_t         buffer_size,          /* IN */
    caddr_t             buffer,               /* IN */
    fsal_size_t        * write_amount         /* OUT */
);

fsal_status_t FSAL_close(
    fsal_file_t        * file_descriptor /* IN */
);

fsal_status_t FSAL_close_by_fileid(
    fsal_file_t        * file_descriptor /* IN */,
    fsal_u64_t           fileid ) ;


fsal_status_t FSAL_readlink(
    fsal_handle_t         * linkhandle,     /* IN */
    fsal_op_context_t     * p_context,              /* IN */
    fsal_path_t           * p_link_content, /* OUT */
    fsal_attrib_list_t    * link_attributes /* [ IN/OUT ] */
);

fsal_status_t FSAL_symlink(
    fsal_handle_t         * parent_directory_handle,        /* IN */
    fsal_name_t           * p_linkname,                /* IN */
    fsal_path_t           * p_linkcontent,                /* IN */
    fsal_op_context_t     * p_context,              /* IN */
    fsal_accessmode_t       accessmode,        /* IN (ignored); */
    fsal_handle_t         * link_handle,        /* OUT */
    fsal_attrib_list_t    * link_attributes        /* [ IN/OUT ] */
);

fsal_status_t FSAL_rename(
    fsal_handle_t         * old_parentdir_handle,        /* IN */
    fsal_name_t           * p_old_name,                        /* IN */
    fsal_handle_t         * new_parentdir_handle,        /* IN */
    fsal_name_t           * p_new_name,                        /* IN */
    fsal_op_context_t     * p_context,              /* IN */
    fsal_attrib_list_t         * src_dir_attributes,                /* [ IN/OUT ] */
    fsal_attrib_list_t        * tgt_dir_attributes                /* [ IN/OUT ] */
);

fsal_status_t FSAL_unlink(
    fsal_handle_t           * parentdir_handle,        /* IN */
    fsal_name_t             * p_object_name,               /* IN */
    fsal_op_context_t       * p_context,              /* IN */
    fsal_attrib_list_t      * parentdir_attributes     /* [IN/OUT ] */
);

fsal_status_t FSAL_mknode(
    fsal_handle_t             * parentdir_handle,       /* IN */
    fsal_name_t               * p_node_name,            /* IN */
    fsal_op_context_t         * p_context,              /* IN */
    fsal_accessmode_t         accessmode,               /* IN */
    fsal_nodetype_t           nodetype,                 /* IN */
    fsal_dev_t                * dev,                    /* IN */
    fsal_handle_t             * p_object_handle,        /* OUT */
    fsal_attrib_list_t        * node_attributes         /* [ IN/OUT ] */
);

fsal_status_t  FSAL_static_fsinfo(
    fsal_handle_t       *   filehandle,       /* IN */
    fsal_op_context_t   *   p_context,        /* IN */
    fsal_staticfsinfo_t *   staticinfo        /* OUT */
);

fsal_status_t  FSAL_dynamic_fsinfo(
    fsal_handle_t        *   filehandle,         /* IN */
    fsal_op_context_t    *   p_context,          /* IN */
    fsal_dynamicfsinfo_t *   dynamicinfo         /* OUT */
);

fsal_status_t  FSAL_rcp(
    fsal_handle_t           *   filehandle,         /* IN */
    fsal_op_context_t       *   p_context,          /* IN */
    fsal_path_t             *   p_local_path,       /* IN */
    fsal_rcpflag_t            transfer_opt          /* IN */
);

fsal_status_t  FSAL_rcp_by_name(
    fsal_handle_t             * filehandle,         /* IN */
    fsal_name_t               * pfilename,          /* IN */
    fsal_op_context_t         * p_context,          /* IN */
    fsal_path_t               * p_local_path,       /* IN */
    fsal_rcpflag_t            transfer_opt          /* IN */
);

fsal_status_t  FSAL_rcp_by_fileid(
    fsal_handle_t             * filehandle,         /* IN */
    fsal_u64_t                  fileid,             /* IN */
    fsal_op_context_t         * p_context,          /* IN */
    fsal_path_t               * p_local_path,       /* IN */
    fsal_rcpflag_t            transfer_opt          /* IN */
);


/* To be called before exiting */
fsal_status_t  FSAL_terminate();


#ifndef _USE_SWIG

/******************************************************
 *                FSAL locks management.
 ******************************************************/

fsal_status_t  FSAL_lock(
    fsal_handle_t           * objecthandle,         /* IN */
    fsal_op_context_t       * p_context,            /* IN */
    fsal_lockparam_t        * lock_info,            /* IN */
    fsal_lockdesc_t         * lock_descriptor       /* OUT */
);

fsal_status_t  FSAL_changelock(
    fsal_lockdesc_t         * lock_descriptor,      /* IN / OUT */
    fsal_lockparam_t        * lock_info             /* IN */
);

fsal_status_t  FSAL_unlock(
    fsal_lockdesc_t * lock_descriptor         /* IN/OUT */
);


/******************************************************
 *          FSAL extended attributes management.
 ******************************************************/

/** cookie for reading attrs from the first one */
#define XATTRS_READLIST_FROM_BEGINNING  (0)

/** An extented attribute entry */
typedef struct fsal_xattrent__
{
  unsigned int         xattr_id;         /**< xattr index */
  fsal_name_t          xattr_name;       /**< attribute name  */
  unsigned int         xattr_cookie;     /**< cookie for getting xattrs list from the next entry */
  fsal_attrib_list_t   attributes;       /**< entry attributes (if supported) */
  
} fsal_xattrent_t;


/**
 * Retrieves the list of extended attributes for an object in the filesystem.
 * 
 * \param p_objecthandle Handle of the object we want to get extended attributes.
 * \param cookie index of the next entry to be returned.
 * \param p_context pointer to the current security context.
 * \param xattrs_tab a table for storing extended attributes list to.
 * \param xattrs_tabsize the maximum number of xattr entries that xattrs_tab
 *            can contain.
 * \param p_nb_returned the number of xattr entries actually stored in xattrs_tab.
 * \param end_of_list this boolean indicates that the end of xattrs list has been reached.
 */ 
fsal_status_t FSAL_ListXAttrs(
    fsal_handle_t     * p_objecthandle,  /* IN */
    unsigned int        cookie,          /* IN */
    fsal_op_context_t * p_context,       /* IN */
    fsal_xattrent_t   * xattrs_tab,      /* IN/OUT */
    unsigned int        xattrs_tabsize,  /* IN */
    unsigned int      * p_nb_returned,   /* OUT */
    int               * end_of_list      /* OUT */
);

/**
 * Get the index of an xattr based on its name
 *
 * \param p_objecthandle Handle of the object you want to get attribute for.
 * \param xattr_name the name of the attribute to be read.
 * \param pxattr_id found xattr_id
 *   
 * \return ERR_FSAL_NO_ERROR if xattr_name exists, ERR_FSAL_NOENT otherwise
 */
fsal_status_t FSAL_GetXAttrIdByName(
    fsal_handle_t     * p_objecthandle,  /* IN */
    const fsal_name_t * xattr_name,      /* IN */
    unsigned int      * pxattr_id        /* OUT */
);

/**
 * Get the value of an extended attribute from its name.
 *
 * \param p_objecthandle Handle of the object you want to get attribute for.
 * \param xattr_name the name of the attribute to be read.
 * \param p_context pointer to the current security context.
 * \param buffer_addr address of the buffer where the xattr value is to be stored.
 * \param buffer_size size of the buffer where the xattr value is to be stored.
 * \param p_output_size size of the data actually stored into the buffer.
 */
fsal_status_t FSAL_GetXAttrValueByName(
    fsal_handle_t     * p_objecthandle,  /* IN */
    const fsal_name_t * xattr_name,      /* IN */
    fsal_op_context_t * p_context,       /* IN */
    caddr_t             buffer_addr,     /* IN/OUT */
    size_t              buffer_size,     /* IN */
    size_t            * p_output_size    /* OUT */
);

/**
 * Get the value of an extended attribute from its index.
 *
 * \param p_objecthandle Handle of the object you want to get attribute for.
 * \param xattr_name the name of the attribute to be read.
 * \param p_context pointer to the current security context.
 * \param buffer_addr address of the buffer where the xattr value is to be stored.
 * \param buffer_size size of the buffer where the xattr value is to be stored.
 * \param p_output_size size of the data actually stored into the buffer.
 */
fsal_status_t FSAL_GetXAttrValueById(
    fsal_handle_t     * p_objecthandle,  /* IN */
    unsigned int        xattr_id,        /* IN */
    fsal_op_context_t * p_context,       /* IN */
    caddr_t             buffer_addr,     /* IN/OUT */
    size_t              buffer_size,     /* IN */
    size_t            * p_output_size    /* OUT */
);


/**
 * Set the value of an extended attribute.
 *
 * \param p_objecthandle Handle of the object you want to set attribute for.
 * \param xattr_name the name of the attribute to be written.
 * \param p_context pointer to the current security context.
 * \param buffer_addr address of the buffer where the xattr value is stored.
 * \param buffer_size size of the buffer where the xattr value is stored.
 * \param create this boolean specifies if the attribute is created
 *               if it does not exist.
 */
fsal_status_t FSAL_SetXAttrValue(
    fsal_handle_t     * p_objecthandle,  /* IN */
    const fsal_name_t * xattr_name,      /* IN */
    caddr_t             buffer_addr,     /* IN */
    size_t              buffer_size,     /* IN */
    int                 create           /* IN */
);


/**
 * Get the attributes of an extended attribute from its index.
 *
 * \param p_objecthandle Handle of the object you want to get attribute for.
 * \param p_context pointer to the current security context.
 * \param xattr_cookie xattr's cookie (as returned by listxattrs).
 * \param p_attrs xattr's attributes.
 */
fsal_status_t FSAL_GetXAttrAttrs(
    fsal_handle_t     *  p_objecthandle,  /* IN */
    fsal_op_context_t *  p_context,       /* IN */
    unsigned int         xattr_id,        /* IN */
    fsal_attrib_list_t * p_attrs          /**< IN/OUT xattr attributes (if supported) */
);


/******************************************************
 *                FSAL miscelaneous tools.
 ******************************************************/

/* Note : one per client thread */
void FSAL_get_stats(
    fsal_statistics_t   * stats,   /* OUT */
    fsal_boolean_t    reset        /* IN */
);

/* Return the name of the underlying file system (used for traces) */
char * FSAL_GetFSName();


/******************************************************
 *                Standard convertion routines.
 ******************************************************/

/**
 * fsal2unix_mode:
 * Convert FSAL mode to posix mode.
 *
 * \param fsal_mode (input):
 *        The FSAL mode to be translated.
 *
 * \return The posix mode associated to fsal_mode.
 */
mode_t fsal2unix_mode( fsal_accessmode_t fsal_mode );



/**
 * unix2fsal_mode:
 * Convert posix mode to FSAL mode.
 *
 * \param unix_mode (input):
 *        The posix mode to be translated.
 *
 * \return The FSAL mode associated to unix_mode.
 */
fsal_accessmode_t unix2fsal_mode(  mode_t unix_mode );

/* The following functions are used in Cache_Inode_Asynch mode */

fsal_status_t FSAL_setattr_access(
    fsal_op_context_t          * p_context,             /* IN */
    fsal_attrib_list_t         * candidate_attributes,  /* IN */
    fsal_attrib_list_t         * object_attributes      /* IN */
) ;


fsal_status_t FSAL_merge_attrs( fsal_attrib_list_t * pinit_attr,         /* IN */
                                fsal_attrib_list_t * pnew_attr,          /* IN */
                                fsal_attrib_list_t * presult_attr ) ;    /* OUT */ 

fsal_status_t FSAL_rename_access( 
	fsal_op_context_t  * pcontext,             /* IN */
        fsal_attrib_list_t * pattrsrc,             /* IN */
	fsal_attrib_list_t * pattrdest ) ;         /* IN */

fsal_status_t FSAL_unlink_access(
        fsal_op_context_t  * pcontext,             /* IN */
        fsal_attrib_list_t * pattr ) ;             /* IN */


fsal_status_t FSAL_create_access(
        fsal_op_context_t  * pcontext,             /* IN */
        fsal_attrib_list_t * pattr ) ;             /* IN */

fsal_status_t FSAL_link_access(
        fsal_op_context_t  * pcontext,             /* IN */
        fsal_attrib_list_t * pattr ) ;             /* IN */

#endif /* ! _USE_SWIG */

#endif /* _FSAL_H */
