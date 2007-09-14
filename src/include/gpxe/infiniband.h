#ifndef _GPXE_INFINIBAND_H
#define _GPXE_INFINIBAND_H

/** @file
 *
 * Infiniband protocol
 *
 */

#include <stdint.h>
#include <gpxe/netdevice.h>

/** An Infiniband Global Identifier */
struct ib_gid {
	uint8_t bytes[16];
};

/** An Infiniband Global Route Header */
struct ib_global_route_header {
	/** IP version, traffic class, and flow label
	 *
	 *  4 bits : Version of the GRH
	 *  8 bits : Traffic class
	 * 20 bits : Flow label
	 */
	uint32_t ipver_tclass_flowlabel;
	/** Payload length */
	uint16_t paylen;
	/** Next header */
	uint8_t nxthdr;
	/** Hop limit */
	uint8_t hoplmt;
	/** Source GID */
	struct ib_gid sgid;
	/** Destiniation GID */
	struct ib_gid dgid;
} __attribute__ (( packed ));

/** Infiniband MAC address length */
#define IB_ALEN 20

/** An Infiniband MAC address */
struct ib_mac {
	/** Queue pair number
	 *
	 * MSB must be zero; QPNs are only 24-bit.
	 */
	uint32_t qpn;
	/** Port GID */
	struct ib_gid gid;
} __attribute__ (( packed ));

/** Infiniband link-layer header length */
#define IB_HLEN 4

/** An Infiniband link-layer header */
struct ibhdr {
	/** Network-layer protocol */
	uint16_t proto;
	/** Reserved, must be zero */
	uint16_t reserved;
} __attribute__ (( packed ));

/** An Infiniband Work Queue */
struct ib_work_queue {
	/** Number of work queue entries */
	unsigned int num_wqes;
	/** Posted index
	 *
	 * This is the index of the most recently posted entry.
	 */
	unsigned int posted;
	/** Driver-private data
	 *
	 * Typically used to hold the address of the work queue.
	 */
	void *priv;
	/** I/O buffers assigned to work queue */
	struct io_buffer *iobuf[0];
};

/** An Infiniband Queue Pair */
struct ib_queue_pair {
	/** Queue Pair Number */
	uint32_t qpn;
	/** Send queue */
	struct ib_work_queue send;
	/** Receive queue */
	struct ib_work_queue recv;
};

/** An Infiniband Address Vector */
struct ib_address_vector {
	
};

/**
 * Infiniband device operations
 *
 * These represent a subset of the Infiniband Verbs.
 */
struct ib_device_operations {
	/** Post Send work queue entry
	 *
	 * @v ibdev		Infiniband device
	 * @v iobuf		I/O buffer
	 * @v av		Address vector
	 * @v qp		Queue pair
	 * @ret rc		Return status code
	 *
	 * If this method returns success, the I/O buffer remains
	 * owned by the queue pair.  If this method returns failure,
	 * the I/O buffer is immediately released; the failure is
	 * interpreted as "failure to enqueue buffer".
	 */
	int ( * post_send ) ( struct ib_device *ibdev,
			      struct io_buffer *iobuf,
			      struct ib_address_vector *av,
			      struct ib_queue_pair *qp );
};






extern struct ll_protocol infiniband_protocol;

extern const char * ib_ntoa ( const void *ll_addr );

/**
 * Allocate Infiniband device
 *
 * @v priv_size		Size of driver private data
 * @ret netdev		Network device, or NULL
 */
static inline struct net_device * alloc_ibdev ( size_t priv_size ) {
	struct net_device *netdev;

	netdev = alloc_netdev ( priv_size );
	if ( netdev ) {
		netdev->ll_protocol = &infiniband_protocol;
	}
	return netdev;
}

#endif /* _GPXE_INFINIBAND_H */
