/* RCSid $Id: rhd_qtree.h,v 3.20 2018/10/05 19:46:26 greg Exp $ */
/*
 * Quadtree data structures for holodeck display drivers.
 */
#ifndef _RAD_RHD_QTREE_H_
#define _RAD_RHD_QTREE_H_

#include "color.h"
#include "tonemap.h"
#include "rhdriver.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	DL		0		/* down left */
#define	DR		1		/* down right */
#define	UL		2		/* up left */
#define	UR		3		/* up right */

#define	BRF(i)		(0x1<<(i))	/* branch flag bit */
#define LFF(i)		(0x10<<(i))	/* leaf flag bit */
#define CHF(i)		(0x100<<(i))	/* change flag bit */
#define	CHBRF(i)	(0x101<<(i))	/* changed branch bit */
#define CHLFF(i)	(0x110<<(i))	/* changed leaf bit */
#define BR_ANY		0xf		/* flags for any branches */
#define LF_ANY		0xf0		/* flags for any leaves */
#define CH_ANY		0xf00		/* flags for any change */

typedef struct rtree {
	short	flgs;			/* content flags (defined above) */
	union {
		struct rtree	*b;		/* if branch */
		int	li;			/* if leaf */
	} k[4];				/* children */
}	RTREE;

extern struct rleaves {
	float		(*wp)[3];	/* world intersection point array */
	int32		*wd;		/* world direction array */
	TMbright	*brt;		/* encoded brightness array */
	uby8		(*chr)[3];	/* encoded chrominance array */
	uby8		(*rgb)[3];	/* tone-mapped color array */
	int		nl;		/* count of leaves in our pile */
	int		bl, tl;		/* bottom and top (next) leaf index */
	int		tml;		/* next leaf needing tone-mapping */
	char		*base;		/* base of allocated memory */
}	qtL;			/* our pile of leaves */

#define	is_stump(t)	(!((t)->flgs & (BR_ANY|LF_ANY)))

extern RTREE	qtrunk;		/* trunk of quadtree */
extern double	qtDepthEps;	/* epsilon to compare depths (z fraction) */
extern int	qtMinNodesiz;	/* minimum node dimension (pixels) */

extern int	rayqleft;	/* number of rays to queue before flush */

extern TMstruct	*tmGlobal;	/* global tone-mapping structure */

	/* rhd_qtree.c */
extern int qtAllocLeaves(register int n);
extern void qtFreeLeaves(void);
extern int qtCompost(int pct);
extern void qtReplant(void);
extern int qtFindLeaf(int x, int y);
extern int qtMapLeaves(int redo);
	/* rhd_qtree2c.c rhd_qtree2r.c */
extern void qtRedraw(int x0, int y0, int x1, int y1);
extern void qtUpdate(void);

#ifdef __cplusplus
}
#endif
#endif /* _RAD_RHD_QTREE_H_ */

