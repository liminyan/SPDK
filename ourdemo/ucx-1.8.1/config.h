/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef UCX_CONFIG_H
#define UCX_CONFIG_H


/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Enable assertions */
/* #undef ENABLE_ASSERT */

/* Enable builtin memcpy */
#define ENABLE_BUILTIN_MEMCPY 1

/* Enable collecting data */
#define ENABLE_DEBUG_DATA 0

/* Enable fault injection code */
/* #undef ENABLE_FAULT_INJECTION */

/* Enable memory tracking */
/* #undef ENABLE_MEMTRACK */

/* Enable thread support in UCP and UCT */
#define ENABLE_MT 0

/* Enable checking user parameters */
#define ENABLE_PARAMS_CHECK 0

/* Enable statistics */
/* #undef ENABLE_STATS */

/* Enable symbol override */
#define ENABLE_SYMBOL_OVERRIDE 1

/* Enable tuning */
/* #undef ENABLE_TUNING */

/* bfd_section_size 2-args version */
#define HAVE_1_ARG_BFD_SECTION_SIZE 0

/* Huawei Kunpeng 920 */
/* #undef HAVE_AARCH64_HI1620 */

/* Cavium ThunderX1 */
/* #undef HAVE_AARCH64_THUNDERX1 */

/* Cavium ThunderX2 */
/* #undef HAVE_AARCH64_THUNDERX2 */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Check attribute [optimize] */
#define HAVE_ATTRIBUTE_NOOPTIMIZE 1

/* user defined cache line size */
/* #undef HAVE_CACHE_LINE_SIZE */

/* Define to 1 if the system has the type `cap_user_data_t'. */
/* #undef HAVE_CAP_USER_DATA_T */

/* Define to 1 if the system has the type `cap_user_header_t'. */
/* #undef HAVE_CAP_USER_HEADER_T */

/* Define to 1 if you have the `clearenv' function. */
#define HAVE_CLEARENV 1

/* Define to 1 if you have the `cplus_demangle' function. */
#define HAVE_CPLUS_DEMANGLE 1

/* Define to 1 if you have the `cpuset_getaffinity' function. */
/* #undef HAVE_CPUSET_GETAFFINITY */

/* Define to 1 if you have the `cpuset_setaffinity' function. */
/* #undef HAVE_CPUSET_SETAFFINITY */

/* Define to 1 if the system has the type `cpuset_t'. */
/* #undef HAVE_CPUSET_T */

/* Define to 1 if the system has the type `cpu_set_t'. */
#define HAVE_CPU_SET_T 1

/* Enable CUDA support */
/* #undef HAVE_CUDA */

/* Define to 1 if you have the <cuda.h> header file. */
/* #undef HAVE_CUDA_H */

/* Define to 1 if you have the <cuda_runtime.h> header file. */
/* #undef HAVE_CUDA_RUNTIME_H */

/* DC DV support */
/* #undef HAVE_DC_DV */

/* DC EXP support */
#define HAVE_DC_EXP 1

/* Define to 1 if you have the declaration of `asprintf', and to 0 if you
   don't. */
#define HAVE_DECL_ASPRINTF 1

/* Define to 1 if you have the declaration of `basename', and to 0 if you
   don't. */
#define HAVE_DECL_BASENAME 1

/* Define to 1 if you have the declaration of `bfd_get_section_flags', and to
   0 if you don't. */
#define HAVE_DECL_BFD_GET_SECTION_FLAGS 1

/* Define to 1 if you have the declaration of `bfd_get_section_vma', and to 0
   if you don't. */
#define HAVE_DECL_BFD_GET_SECTION_VMA 1

/* Define to 1 if you have the declaration of `bfd_section_flags', and to 0 if
   you don't. */
#define HAVE_DECL_BFD_SECTION_FLAGS 0

/* Define to 1 if you have the declaration of `bfd_section_vma', and to 0 if
   you don't. */
#define HAVE_DECL_BFD_SECTION_VMA 1

/* Define to 1 if you have the declaration of `CPU_ISSET', and to 0 if you
   don't. */
#define HAVE_DECL_CPU_ISSET 1

/* Define to 1 if you have the declaration of `CPU_ZERO', and to 0 if you
   don't. */
#define HAVE_DECL_CPU_ZERO 1

/* Define to 1 if you have the declaration of `ethtool_cmd_speed', and to 0 if
   you don't. */
#define HAVE_DECL_ETHTOOL_CMD_SPEED 1

/* Define to 1 if you have the declaration of `fmemopen', and to 0 if you
   don't. */
#define HAVE_DECL_FMEMOPEN 1

/* Define to 1 if you have the declaration of `F_SETOWN_EX', and to 0 if you
   don't. */
#define HAVE_DECL_F_SETOWN_EX 1

/* Define to 1 if you have the declaration of `gdr_copy_to_mapping', and to 0
   if you don't. */
#define HAVE_DECL_GDR_COPY_TO_MAPPING 1

/* Define to 1 if you have the declaration of `IBV_ACCESS_ON_DEMAND', and to 0
   if you don't. */
#define HAVE_DECL_IBV_ACCESS_ON_DEMAND 1

/* Define to 1 if you have the declaration of `ibv_advise_mr', and to 0 if you
   don't. */
#define HAVE_DECL_IBV_ADVISE_MR 0

/* Define to 1 if you have the declaration of `ibv_alloc_dm', and to 0 if you
   don't. */
#define HAVE_DECL_IBV_ALLOC_DM 0

/* Define to 1 if you have the declaration of `ibv_alloc_td', and to 0 if you
   don't. */
#define HAVE_DECL_IBV_ALLOC_TD 0

/* Define to 1 if you have the declaration of `ibv_cmd_modify_qp', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_CMD_MODIFY_QP 1

/* Define to 1 if you have the declaration of
   `IBV_CREATE_CQ_ATTR_IGNORE_OVERRUN', and to 0 if you don't. */
#define HAVE_DECL_IBV_CREATE_CQ_ATTR_IGNORE_OVERRUN 0

/* Define to 1 if you have the declaration of `ibv_create_qp_ex', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_CREATE_QP_EX 1

/* Define to 1 if you have the declaration of `ibv_create_srq', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_CREATE_SRQ 1

/* Define to 1 if you have the declaration of `ibv_create_srq_ex', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_CREATE_SRQ_EX 1

/* Define to 1 if you have the declaration of `IBV_EVENT_GID_CHANGE', and to 0
   if you don't. */
#define HAVE_DECL_IBV_EVENT_GID_CHANGE 1

/* Define to 1 if you have the declaration of `ibv_event_type_str', and to 0
   if you don't. */
#define HAVE_DECL_IBV_EVENT_TYPE_STR 1

/* Define to 1 if you have the declaration of `IBV_EXP_ACCESS_ALLOCATE_MR',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_ACCESS_ALLOCATE_MR 1

/* Define to 1 if you have the declaration of `IBV_EXP_ACCESS_ON_DEMAND', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_ACCESS_ON_DEMAND 1

/* Define to 1 if you have the declaration of `ibv_exp_alloc_dm', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_EXP_ALLOC_DM 1

/* Define to 1 if you have the declaration of `IBV_EXP_ATOMIC_HCA_REPLY_BE',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_ATOMIC_HCA_REPLY_BE 1

/* Define to 1 if you have the declaration of `IBV_EXP_CQ_IGNORE_OVERRUN', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_CQ_IGNORE_OVERRUN 1

/* Define to 1 if you have the declaration of `IBV_EXP_CQ_MODERATION', and to
   0 if you don't. */
#define HAVE_DECL_IBV_EXP_CQ_MODERATION 1

/* Define to 1 if you have the declaration of `ibv_exp_create_qp', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_EXP_CREATE_QP 1

/* Define to 1 if you have the declaration of `ibv_exp_create_res_domain', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_CREATE_RES_DOMAIN 1

/* Define to 1 if you have the declaration of `ibv_exp_create_srq', and to 0
   if you don't. */
#define HAVE_DECL_IBV_EXP_CREATE_SRQ 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_DCT_OOO_RW_DATA_PLACEMENT', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_DCT_OOO_RW_DATA_PLACEMENT 1

/* Define to 1 if you have the declaration of `ibv_exp_destroy_res_domain',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_DESTROY_RES_DOMAIN 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_DEVICE_ATTR_PCI_ATOMIC_CAPS', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_DEVICE_ATTR_PCI_ATOMIC_CAPS 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_DEVICE_ATTR_RESERVED_2', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_DEVICE_ATTR_RESERVED_2 1

/* Define to 1 if you have the declaration of `IBV_EXP_DEVICE_DC_TRANSPORT',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_DEVICE_DC_TRANSPORT 1

/* Define to 1 if you have the declaration of `IBV_EXP_DEVICE_MR_ALLOCATE',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_DEVICE_MR_ALLOCATE 1

/* Define to 1 if you have the declaration of `IBV_EXP_MR_FIXED_BUFFER_SIZE',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_MR_FIXED_BUFFER_SIZE 1

/* Define to 1 if you have the declaration of `IBV_EXP_MR_INDIRECT_KLMS', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_MR_INDIRECT_KLMS 1

/* Define to 1 if you have the declaration of `IBV_EXP_ODP_SUPPORT_IMPLICIT',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_ODP_SUPPORT_IMPLICIT 1

/* Define to 1 if you have the declaration of `ibv_exp_post_send', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_EXP_POST_SEND 1

/* Define to 1 if you have the declaration of `ibv_exp_prefetch_mr', and to 0
   if you don't. */
#define HAVE_DECL_IBV_EXP_PREFETCH_MR 1

/* Define to 1 if you have the declaration of `IBV_EXP_PREFETCH_WRITE_ACCESS',
   and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_PREFETCH_WRITE_ACCESS 1

/* Define to 1 if you have the declaration of `IBV_EXP_QPT_DC_INI', and to 0
   if you don't. */
#define HAVE_DECL_IBV_EXP_QPT_DC_INI 1

/* Define to 1 if you have the declaration of `IBV_EXP_QP_CREATE_UMR', and to
   0 if you don't. */
#define HAVE_DECL_IBV_EXP_QP_CREATE_UMR 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_QP_INIT_ATTR_ATOMICS_ARG', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_QP_INIT_ATTR_ATOMICS_ARG 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_QP_INIT_ATTR_RES_DOMAIN', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_QP_INIT_ATTR_RES_DOMAIN 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_QP_OOO_RW_DATA_PLACEMENT', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_QP_OOO_RW_DATA_PLACEMENT 1

/* Define to 1 if you have the declaration of `ibv_exp_query_device', and to 0
   if you don't. */
#define HAVE_DECL_IBV_EXP_QUERY_DEVICE 1

/* Define to 1 if you have the declaration of `ibv_exp_query_gid_attr', and to
   0 if you don't. */
#define HAVE_DECL_IBV_EXP_QUERY_GID_ATTR 1

/* Define to 1 if you have the declaration of `ibv_exp_reg_mr', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_EXP_REG_MR 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_RES_DOMAIN_THREAD_MODEL', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_RES_DOMAIN_THREAD_MODEL 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_SEND_EXT_ATOMIC_INLINE', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_SEND_EXT_ATOMIC_INLINE 1

/* Define to 1 if you have the declaration of `ibv_exp_setenv', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_EXP_SETENV 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_WR_EXT_MASKED_ATOMIC_CMP_AND_SWP', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_WR_EXT_MASKED_ATOMIC_CMP_AND_SWP 1

/* Define to 1 if you have the declaration of
   `IBV_EXP_WR_EXT_MASKED_ATOMIC_FETCH_AND_ADD', and to 0 if you don't. */
#define HAVE_DECL_IBV_EXP_WR_EXT_MASKED_ATOMIC_FETCH_AND_ADD 1

/* Define to 1 if you have the declaration of `IBV_EXP_WR_NOP', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_EXP_WR_NOP 1

/* Define to 1 if you have the declaration of `ibv_get_async_event', and to 0
   if you don't. */
#define HAVE_DECL_IBV_GET_ASYNC_EVENT 1

/* Define to 1 if you have the declaration of `ibv_get_device_name', and to 0
   if you don't. */
#define HAVE_DECL_IBV_GET_DEVICE_NAME 1

/* Define to 1 if you have the declaration of `IBV_LINK_LAYER_ETHERNET', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_LINK_LAYER_ETHERNET 1

/* Define to 1 if you have the declaration of `IBV_LINK_LAYER_INFINIBAND', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_LINK_LAYER_INFINIBAND 1

/* Define to 1 if you have the declaration of `ibv_mlx5_exp_get_cq_info', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_MLX5_EXP_GET_CQ_INFO 1

/* Define to 1 if you have the declaration of `ibv_mlx5_exp_get_qp_info', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_MLX5_EXP_GET_QP_INFO 1

/* Define to 1 if you have the declaration of `ibv_mlx5_exp_get_srq_info', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_MLX5_EXP_GET_SRQ_INFO 1

/* Define to 1 if you have the declaration of `ibv_mlx5_exp_update_cq_ci', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_MLX5_EXP_UPDATE_CQ_CI 1

/* Define to 1 if you have the declaration of `IBV_ODP_SUPPORT_IMPLICIT', and
   to 0 if you don't. */
#define HAVE_DECL_IBV_ODP_SUPPORT_IMPLICIT 0

/* have upstream ibv_query_device_ex */
#define HAVE_DECL_IBV_QUERY_DEVICE_EX 1

/* Define to 1 if you have the declaration of `ibv_query_gid', and to 0 if you
   don't. */
#define HAVE_DECL_IBV_QUERY_GID 1

/* Define to 1 if you have the declaration of `ibv_wc_status_str', and to 0 if
   you don't. */
#define HAVE_DECL_IBV_WC_STATUS_STR 1

/* Define to 1 if you have the declaration of `MADV_FREE', and to 0 if you
   don't. */
#define HAVE_DECL_MADV_FREE 0

/* Define to 1 if you have the declaration of `MADV_REMOVE', and to 0 if you
   don't. */
#define HAVE_DECL_MADV_REMOVE 1

/* Define to 1 if you have the declaration of
   `MLX5DV_CQ_INIT_ATTR_MASK_CQE_SIZE', and to 0 if you don't. */
#define HAVE_DECL_MLX5DV_CQ_INIT_ATTR_MASK_CQE_SIZE 0

/* Define to 1 if you have the declaration of `mlx5dv_create_qp', and to 0 if
   you don't. */
#define HAVE_DECL_MLX5DV_CREATE_QP 0

/* Define to 1 if you have the declaration of `MLX5DV_DCTYPE_DCT', and to 0 if
   you don't. */
#define HAVE_DECL_MLX5DV_DCTYPE_DCT 0

/* Define to 1 if you have the declaration of `mlx5dv_init_obj', and to 0 if
   you don't. */
#define HAVE_DECL_MLX5DV_INIT_OBJ 1

/* Define to 1 if you have the declaration of `mlx5dv_is_supported', and to 0
   if you don't. */
#define HAVE_DECL_MLX5DV_IS_SUPPORTED 0

/* Define to 1 if you have the declaration of `MLX5DV_OBJ_AH', and to 0 if you
   don't. */
#define HAVE_DECL_MLX5DV_OBJ_AH 0

/* Define to 1 if you have the declaration of
   `MLX5DV_QP_CREATE_ALLOW_SCATTER_TO_CQE', and to 0 if you don't. */
#define HAVE_DECL_MLX5DV_QP_CREATE_ALLOW_SCATTER_TO_CQE 0

/* Define to 1 if you have the declaration of `MLX5_WQE_CTRL_SOLICITED', and
   to 0 if you don't. */
#define HAVE_DECL_MLX5_WQE_CTRL_SOLICITED 1

/* Define to 1 if you have the declaration of `POSIX_MADV_DONTNEED', and to 0
   if you don't. */
#define HAVE_DECL_POSIX_MADV_DONTNEED 1

/* Define to 1 if you have the declaration of `PR_SET_PTRACER', and to 0 if
   you don't. */
#define HAVE_DECL_PR_SET_PTRACER 1

/* Define to 1 if you have the declaration of `rdma_establish', and to 0 if
   you don't. */
#define HAVE_DECL_RDMA_ESTABLISH 1

/* Define to 1 if you have the declaration of `rdma_init_qp_attr', and to 0 if
   you don't. */
#define HAVE_DECL_RDMA_INIT_QP_ATTR 1

/* Define to 1 if you have the declaration of `SPEED_UNKNOWN', and to 0 if you
   don't. */
#define HAVE_DECL_SPEED_UNKNOWN 1

/* Define to 1 if you have the declaration of `strerror_r', and to 0 if you
   don't. */
#define HAVE_DECL_STRERROR_R 1

/* Define to 1 if you have the declaration of `SYS_brk', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_BRK 1

/* Define to 1 if you have the declaration of `SYS_ipc', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_IPC 0

/* Define to 1 if you have the declaration of `SYS_madvise', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_MADVISE 1

/* Define to 1 if you have the declaration of `SYS_mmap', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_MMAP 1

/* Define to 1 if you have the declaration of `SYS_mremap', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_MREMAP 1

/* Define to 1 if you have the declaration of `SYS_munmap', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_MUNMAP 1

/* Define to 1 if you have the declaration of `SYS_shmat', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_SHMAT 1

/* Define to 1 if you have the declaration of `SYS_shmdt', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_SHMDT 1

/* Define to 1 if you have the declaration of `__ppc_get_timebase_freq', and
   to 0 if you don't. */
#define HAVE_DECL___PPC_GET_TIMEBASE_FREQ 0

/* Enable detailed backtrace */
#define HAVE_DETAILED_BACKTRACE 1

/* DEVX support */
/* #undef HAVE_DEVX */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <endian.h,> header file. */
/* #undef HAVE_ENDIAN_H_ */

/* IB UMR support */
#define HAVE_EXP_UMR 1

/* IB UMR KSM support */
#define HAVE_EXP_UMR_KSM 1

/* Define to 1 if you have the <gdrapi.h> header file. */
#define HAVE_GDRAPI_H 1

/* Define to 1 if you have the <hip_runtime.h> header file. */
/* #undef HAVE_HIP_RUNTIME_H */

/* Define to 1 if you have the <hsa_ext_amd.h> header file. */
/* #undef HAVE_HSA_EXT_AMD_H */

/* Define to 1 if you have the <hsa.h> header file. */
/* #undef HAVE_HSA_H */

/* high-resolution hardware timer disabled */
#define HAVE_HW_TIMER 1

/* IB support */
#define HAVE_IB 1

/* Device Memory support */
#define HAVE_IBV_DM 1

/* Device Memory support (EXP) */
#define HAVE_IBV_EXP_DM 1

/* IB QP Create UMR support */
#define HAVE_IBV_EXP_QP_CREATE_UMR 1

/* Support UMR max caps v2 */
/* #undef HAVE_IBV_EXP_QP_CREATE_UMR_CAPS */

/* IB resource domain */
#define HAVE_IBV_EXP_RES_DOMAIN 1

/* IB extended atomics support */
#define HAVE_IB_EXT_ATOMICS 1

/* struct in6_addr has s6_addr32 member */
#define HAVE_IN6_ADDR_S6_ADDR32 1

/* struct in6_addr is BSD-style */
/* #undef HAVE_IN6_ADDR_U6_ADDR32 */

/* Define to 1 if you have the <infiniband/mlx5dv.h> header file. */
#define HAVE_INFINIBAND_MLX5DV_H 1

/* Define to 1 if you have the <infiniband/mlx5_hw.h> header file. */
#define HAVE_INFINIBAND_MLX5_HW_H 1

/* Define to 1 if you have the <infiniband/tm_types.h> header file. */
/* #undef HAVE_INFINIBAND_TM_TYPES_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* struct iphdr has daddr member */
/* #undef HAVE_IPHDR_DADDR */

/* struct ip has ip_dst member */
#define HAVE_IP_IP_DST 1

/* Define to 1 if you have the <jni.h> header file. */
/* #undef HAVE_JNI_H */

/* Define to 1 if you have the <jni_md.h> header file. */
/* #undef HAVE_JNI_MD_H */

/* Define to 1 if you have the <libgen.h> header file. */
#define HAVE_LIBGEN_H 1

/* Define to 1 if you have the `rt' library (-lrt). */
#define HAVE_LIBRT 1

/* Define to 1 if you have the <linux/futex.h> header file. */
#define HAVE_LINUX_FUTEX_H 1

/* Define to 1 if you have the <linux/ip.h> header file. */
#define HAVE_LINUX_IP_H 1

/* Define to 1 if you have the <linux/mman.h> header file. */
#define HAVE_LINUX_MMAN_H 1

/* Define to 1 if you have the `malloc_get_state' function. */
#define HAVE_MALLOC_GET_STATE 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* malloc hooks support */
#define HAVE_MALLOC_HOOK 1

/* Define to 1 if you have the <malloc_np.h> header file. */
/* #undef HAVE_MALLOC_NP_H */

/* Define to 1 if you have the `malloc_set_state' function. */
#define HAVE_MALLOC_SET_STATE 1

/* Define to 1 if you have the `malloc_trim' function. */
#define HAVE_MALLOC_TRIM 1

/* have masked atomic endianness */
#define HAVE_MASKED_ATOMICS_ENDIANNESS 1

/* Define to 1 if you have the `memalign' function. */
#define HAVE_MEMALIGN 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* mlx5 bare-metal support */
#define HAVE_MLX5_HW 1

/* mlx5 UD bare-metal support */
#define HAVE_MLX5_HW_UD 1

/* MPI support */
/* #undef HAVE_MPI */

/* Define to 1 if you have the `mremap' function. */
#define HAVE_MREMAP 1

/* Define to 1 if you have the <netinet/ip.h> header file. */
#define HAVE_NETINET_IP_H 1

/* Define to 1 if you have the <net/ethernet.h> header file. */
#define HAVE_NET_ETHERNET_H 1

/* Define to 1 to enable NUMA support */
#define HAVE_NUMA 1

/* Define to 1 if you have the <numaif.h> header file. */
#define HAVE_NUMAIF_H 1

/* Define to 1 if you have the <numa.h> header file. */
#define HAVE_NUMA_H 1

/* ODP support */
#define HAVE_ODP 1

/* Implicit ODP support */
#define HAVE_ODP_IMPLICIT 1

/* Define to 1 if you have the `posix_memalign' function. */
#define HAVE_POSIX_MEMALIGN 1

/* Prefetch support */
#define HAVE_PREFETCH 1

/* Enable profiling */
/* #undef HAVE_PROFILING */

/* Define to 1 if you have the <pthread_np.h> header file. */
/* #undef HAVE_PTHREAD_NP_H */

/* RDMACM QP less support */
#define HAVE_RDMACM_QP_LESS 1

/* RTE support */
/* #undef HAVE_RTE */

/* Define to 1 if you have the `sched_getaffinity' function. */
#define HAVE_SCHED_GETAFFINITY 1

/* Define to 1 if you have the `sched_setaffinity' function. */
#define HAVE_SCHED_SETAFFINITY 1

/* struct sigaction has sa_restorer member */
#define HAVE_SIGACTION_SA_RESTORER 1

/* struct sigevent has sigev_notify_thread_id */
/* #undef HAVE_SIGEVENT_SIGEV_NOTIFY_THREAD_ID */

/* struct sigevent has _sigev_un._tid */
#define HAVE_SIGEVENT_SIGEV_UN_TID 1

/* Define to 1 if the system has the type `sighandler_t'. */
#define HAVE_SIGHANDLER_T 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strerror_r' function. */
#define HAVE_STRERROR_R 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if the system has the type `struct bitmask'. */
#define HAVE_STRUCT_BITMASK 1

/* Define to 1 if the system has the type `struct dl_phdr_info'. */
#define HAVE_STRUCT_DL_PHDR_INFO 1

/* Define to 1 if `element.dct' is a member of `struct ibv_async_event'. */
#define HAVE_STRUCT_IBV_ASYNC_EVENT_ELEMENT_DCT 1

/* Define to 1 if `dc_offload_params' is a member of `struct
   ibv_exp_create_srq_attr'. */
#define HAVE_STRUCT_IBV_EXP_CREATE_SRQ_ATTR_DC_OFFLOAD_PARAMS 1

/* Define to 1 if `exp_device_cap_flags' is a member of `struct
   ibv_exp_device_attr'. */
#define HAVE_STRUCT_IBV_EXP_DEVICE_ATTR_EXP_DEVICE_CAP_FLAGS 1

/* Define to 1 if `odp_caps' is a member of `struct ibv_exp_device_attr'. */
#define HAVE_STRUCT_IBV_EXP_DEVICE_ATTR_ODP_CAPS 1

/* Define to 1 if `odp_caps.per_transport_caps.dc_odp_caps' is a member of
   `struct ibv_exp_device_attr'. */
#define HAVE_STRUCT_IBV_EXP_DEVICE_ATTR_ODP_CAPS_PER_TRANSPORT_CAPS_DC_ODP_CAPS 1

/* Define to 1 if `odp_mr_max_size' is a member of `struct
   ibv_exp_device_attr'. */
#define HAVE_STRUCT_IBV_EXP_DEVICE_ATTR_ODP_MR_MAX_SIZE 1

/* Define to 1 if `max_inl_recv' is a member of `struct ibv_exp_qp_init_attr'.
   */
#define HAVE_STRUCT_IBV_EXP_QP_INIT_ATTR_MAX_INL_RECV 1

/* Define to 1 if `umr_caps' is a member of `struct ibv_exp_qp_init_attr'. */
/* #undef HAVE_STRUCT_IBV_EXP_QP_INIT_ATTR_UMR_CAPS */

/* Define to 1 if `bf.need_lock' is a member of `struct ibv_mlx5_qp_info'. */
#define HAVE_STRUCT_IBV_MLX5_QP_INFO_BF_NEED_LOCK 1

/* Define to 1 if `flags' is a member of `struct ibv_tm_caps'. */
/* #undef HAVE_STRUCT_IBV_TM_CAPS_FLAGS */

/* Define to 1 if `cq_uar' is a member of `struct mlx5dv_cq'. */
#define HAVE_STRUCT_MLX5DV_CQ_CQ_UAR 1

/* Define to 1 if `ibv_ah' is a member of `struct mlx5_ah'. */
#define HAVE_STRUCT_MLX5_AH_IBV_AH 1

/* Define to 1 if `ib_stride_index' is a member of `struct mlx5_cqe64'. */
#define HAVE_STRUCT_MLX5_CQE64_IB_STRIDE_INDEX 1

/* Define to 1 if `rmac' is a member of `struct mlx5_grh_av'. */
#define HAVE_STRUCT_MLX5_GRH_AV_RMAC 1

/* Define to 1 if `cmd_qp' is a member of `struct mlx5_srq'. */
#define HAVE_STRUCT_MLX5_SRQ_CMD_QP 1

/* Define to 1 if `base' is a member of `struct mlx5_wqe_av'. */
#define HAVE_STRUCT_MLX5_WQE_AV_BASE 1

/* Linux capability API support */
/* #undef HAVE_SYS_CAPABILITY_H */

/* Define to 1 if you have the <sys/cpuset.h> header file. */
/* #undef HAVE_SYS_CPUSET_H */

/* Define to 1 if you have the <sys/endian.h> header file. */
/* #undef HAVE_SYS_ENDIAN_H */

/* Define to 1 if you have the <sys/epoll.h> header file. */
#define HAVE_SYS_EPOLL_H 1

/* Define to 1 if you have the <sys/eventfd.h> header file. */
#define HAVE_SYS_EVENTFD_H 1

/* Define to 1 if you have the <sys/event.h> header file. */
/* #undef HAVE_SYS_EVENT_H */

/* Define to 1 if you have the <sys/platform/ppc.h> header file. */
/* #undef HAVE_SYS_PLATFORM_PPC_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/thr.h> header file. */
/* #undef HAVE_SYS_THR_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* DC transport support */
#define HAVE_TL_DC 1

/* RC transport support */
#define HAVE_TL_RC 1

/* UD transport support */
#define HAVE_TL_UD 1

/* Defined if UGNI transport exists */
/* #undef HAVE_TL_UGNI */

/* Use ptmalloc-2.8.6 version */
#define HAVE_UCM_PTMALLOC286 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* IB experimental verbs */
#define HAVE_VERBS_EXP_H 1

/* Define to 1 if you have the `__aarch64_sync_cache_range' function. */
/* #undef HAVE___AARCH64_SYNC_CACHE_RANGE */

/* Define to 1 if you have the `__clear_cache' function. */
#define HAVE___CLEAR_CACHE 1

/* Define to 1 if you have the `__curbrk' function. */
#define HAVE___CURBRK 1

/* Define to 1 if the system has the type `__sighandler_t'. */
#define HAVE___SIGHANDLER_T 1

/* IB Tag Matching support */
#define IBV_HW_TM 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 to disable Valgrind annotations. */
#define NVALGRIND 1

/* Name of package */
#define PACKAGE "ucx"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "ucx"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "ucx 1.8"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "ucx"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.8"

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if strerror_r returns char *. */
#define STRERROR_R_CHAR_P 1

/* Enable BISTRO hooks */
#define UCM_BISTRO_HOOKS 1

/* Highest log level */
#define UCS_MAX_LOG_LEVEL UCS_LOG_LEVEL_INFO

/* Enable packet header inspection/rewriting in UCT/UD */
#define UCT_UD_EP_DEBUG_HOOKS 0

/* Set aligment assumption for compiler */
/* #undef UCX_ALLOC_ALIGN */

/* UCX configure flags */
#define UCX_CONFIGURE_FLAGS "--disable-logging --disable-debug --disable-assertions --disable-params-check --prefix=/global/home/users/liyiyuan/exe3/ucx-1.8.1/install"

/* UCX module sub-directory */
#define UCX_MODULE_SUBDIR "ucx"

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.8"

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Test loadable modules */
#define test_MODULES ":module"

/* UCM loadable modules */
#define ucm_MODULES ""

/* UCT loadable modules */
#define uct_MODULES ":ib:rdmacm:cma:knem"

/* CUDA loadable modules */
#define uct_cuda_MODULES ":gdrcopy"

/* IB loadable modules */
#define uct_ib_MODULES ":cm"

/* ROCM loadable modules */
#define uct_rocm_MODULES ""

/* Perftest loadable modules */
#define ucx_perftest_MODULES ""


#endif /* UCX_CONFIG_H */

