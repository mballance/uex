/*
 * uex_dpi.h
 *
 *  Created on: Jan 8, 2018
 *      Author: ballance
 */

#ifndef IMPL_SV_UEX_DPI_H_
#define IMPL_SV_UEX_DPI_H_

typedef void *svScope;

#ifdef __cplusplus
extern "C" {
#endif

svScope svGetScope();
svScope svSetScope(const svScope s);
void svAckDisabledState(void);
int svIsDisabledState(void);


#ifdef __cplusplus
}
#endif

void *uex_svScope();

#endif /* IMPL_SV_UEX_DPI_H_ */
