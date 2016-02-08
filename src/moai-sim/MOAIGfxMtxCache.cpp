// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <moai-sim/MOAIGfxMgr.h>
#include <moai-sim/MOAIGfxMtxCache.h>

//================================================================//
// MOAIGfxMtxCache
//================================================================//

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetNormToWndMtx () {

	return this->GetNormToWndMtx ( MOAIGfxMgr::Get ().GetViewRect ());
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetNormToWndMtx ( const ZLRect& wndRect ) {

	float hWidth = wndRect.Width () * 0.5f;
	float hHeight = wndRect.Height () * 0.5f;

	// Wnd
	ZLMatrix4x4 normToWnd;
	normToWnd.Scale ( hWidth, -hHeight, 1.0f );
	
	ZLMatrix4x4 mtx;
	mtx.Translate ( hWidth + wndRect.mXMin, hHeight + wndRect.mYMin, 0.0f );
	normToWnd.Append ( mtx );
	
	return normToWnd;
}

//----------------------------------------------------------------//
const ZLMatrix4x4& MOAIGfxMtxCache::GetMtx ( u32 transformID ) {

	switch ( transformID ) {
	
		case INVERSE_PROJ_MTX:
		
			if ( this->mDirtyFlags & INVERSE_PROJ_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_PROJ_MTX ].Inverse ( this->GetMtx ( PROJ_MTX ));
				this->mDirtyFlags &= ~INVERSE_PROJ_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_PROJ_MTX ];
			
		case INVERSE_UV_MTX:
			
			if ( this->mDirtyFlags & INVERSE_UV_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_UV_MTX ].Inverse ( this->GetMtx ( UV_MTX ));
				this->mDirtyFlags &= ~INVERSE_UV_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_UV_MTX ];
			
		case INVERSE_VIEW_MTX:
			
			if ( this->mDirtyFlags & INVERSE_VIEW_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_VIEW_MTX ].Inverse ( this->GetMtx ( VIEW_MTX ));
				this->mDirtyFlags &= ~INVERSE_VIEW_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_VIEW_MTX ];
			
		case INVERSE_VIEW_PROJ_MTX:
			
			if ( this->mDirtyFlags & INVERSE_WORLD_VIEW_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_WORLD_VIEW_MTX ].Inverse ( this->GetMtx ( VIEW_PROJ_MTX ));
				this->mDirtyFlags &= ~INVERSE_WORLD_VIEW_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_WORLD_VIEW_MTX ];
			
		case INVERSE_WORLD_MTX:
			
			if ( this->mDirtyFlags & INVERSE_WORLD_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_WORLD_MTX ].Inverse ( this->GetMtx ( WORLD_MTX ));
				this->mDirtyFlags &= ~INVERSE_WORLD_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_WORLD_MTX ];
			
		case INVERSE_WORLD_VIEW_MTX:
			
			if ( this->mDirtyFlags & INVERSE_WORLD_VIEW_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_WORLD_VIEW_MTX ].Inverse ( this->GetMtx ( WORLD_VIEW_MTX ));
				this->mDirtyFlags &= ~INVERSE_WORLD_VIEW_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_WORLD_VIEW_MTX ];
			
		case INVERSE_WORLD_VIEW_PROJ_MTX:
			
			if ( this->mDirtyFlags & INVERSE_WORLD_VIEW_PROJ_MTX_MASK ) {
			
				this->mVertexTransforms [ INVERSE_WORLD_VIEW_PROJ_MTX ].Inverse ( this->GetMtx ( WORLD_VIEW_PROJ_MTX ));
				this->mDirtyFlags &= ~INVERSE_WORLD_VIEW_PROJ_MTX_FLAG;
			}
			return this->mVertexTransforms [ INVERSE_WORLD_VIEW_PROJ_MTX ];
			
		case PROJ_MTX:
			
			return this->mVertexTransforms [ PROJ_MTX ];
			
		case UV_MTX:
			
			return this->mVertexTransforms [ UV_MTX ];
			
		case VIEW_MTX:
			
			return this->mVertexTransforms [ VIEW_MTX ];
			
		case VIEW_PROJ_MTX:
			
			if ( this->mDirtyFlags & VIEW_PROJ_MTX_MASK ) {
			
				this->mVertexTransforms [ VIEW_PROJ_MTX ] = this->mVertexTransforms [ VIEW_MTX ];
				this->mVertexTransforms [ VIEW_PROJ_MTX ].Append ( this->mVertexTransforms [ PROJ_MTX ]);
				
				this->mDirtyFlags &= ~VIEW_PROJ_MTX_MASK;
			}
			return this->mVertexTransforms [ VIEW_PROJ_MTX ];
			
		case WORLD_MTX:
			
			return this->mVertexTransforms [ WORLD_MTX ];
			
		case WORLD_VIEW_MTX:
			
			if ( this->mDirtyFlags & WORLD_VIEW_MTX_MASK ) {
			
				this->mVertexTransforms [ WORLD_VIEW_MTX ] = this->mVertexTransforms [ WORLD_MTX ];
				this->mVertexTransforms [ WORLD_VIEW_MTX ].Append ( this->mVertexTransforms [ VIEW_MTX ]);
				
				this->mDirtyFlags &= ~WORLD_VIEW_MTX_MASK;
			}
			return this->mVertexTransforms [ WORLD_VIEW_MTX ];
			
		case WORLD_VIEW_PROJ_MTX:
			
			if ( this->mDirtyFlags & WORLD_VIEW_PROJ_MTX_MASK ) {
			
				this->mVertexTransforms [ WORLD_VIEW_PROJ_MTX ] = this->mVertexTransforms [ WORLD_MTX ];
				this->mVertexTransforms [ WORLD_VIEW_PROJ_MTX ].Append ( this->GetMtx ( VIEW_PROJ_MTX ));
				
				this->mDirtyFlags &= ~WORLD_VIEW_PROJ_MTX_MASK;
			}
			return this->mVertexTransforms [ WORLD_VIEW_PROJ_MTX ];
	}
	
	assert ( false );
	return this->mVertexTransforms [ WORLD_MTX ];
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetWorldToWndMtx () {

	return this->GetWorldToWndMtx ( MOAIGfxMgr::Get ().GetViewRect ());
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetWorldToWndMtx ( const ZLRect& wndRect ) {

	ZLMatrix4x4 worldToWnd = this->GetMtx ( VIEW_PROJ_MTX );
	worldToWnd.Append ( MOAIGfxMtxCache::GetNormToWndMtx ( wndRect ));
	
	return worldToWnd;
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetWndToNormMtx () {

	return this->GetWndToNormMtx ( MOAIGfxMgr::Get ().GetViewRect ());
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetWndToNormMtx ( const ZLRect& wndRect ) {

	float hWidth = wndRect.Width () * 0.5f;
	float hHeight = wndRect.Height () * 0.5f;

	// Inv Wnd
	ZLMatrix4x4 wndToNorm;
	wndToNorm.Translate ( -hWidth - wndRect.mXMin, -hHeight - wndRect.mYMin, 0.0f );
	
	ZLMatrix4x4 mtx;
	mtx.Scale (( 1.0f / hWidth ), -( 1.0f / hHeight ), 1.0f );
	wndToNorm.Append ( mtx );
	
	return wndToNorm;
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetWndToWorldMtx () {

	return this->GetWndToWorldMtx ( MOAIGfxMgr::Get ().GetViewRect ());
}

//----------------------------------------------------------------//
ZLMatrix4x4 MOAIGfxMtxCache::GetWndToWorldMtx ( const ZLRect& wndRect ) {

	ZLMatrix4x4 wndToWorld = MOAIGfxMtxCache::GetWndToNormMtx ( wndRect );
	
	// inv viewproj
	ZLMatrix4x4 mtx = this->GetMtx ( VIEW_PROJ_MTX );
	mtx.Inverse ();
	wndToWorld.Append ( mtx );
	
	return wndToWorld;
}

//----------------------------------------------------------------//
const ZLFrustum& MOAIGfxMtxCache::GetViewVolume () {

	if ( this->mDirtyFlags & VIEW_VOLUME_MASK ) {
		this->mViewVolume.Init ( this->GetMtx ( INVERSE_VIEW_PROJ_MTX ));
		this->mDirtyFlags &= ~VIEW_VOLUME_MASK;
	}
	return this->mViewVolume;
}

//----------------------------------------------------------------//
MOAIGfxMtxCache::MOAIGfxMtxCache () {

	for ( u32 i = 0; i < TOTAL_MATRICES; ++i ) {
		this->mVertexTransforms [ i ].Ident ();
		this->mDirtyFlags = 0;
	}
}

//----------------------------------------------------------------//
MOAIGfxMtxCache::~MOAIGfxMtxCache () {
}

//----------------------------------------------------------------//
void MOAIGfxMtxCache::SetMtx ( u32 transformID ) {

	ZLMatrix4x4 mtx;
	mtx.Ident ();
	this->SetMtx ( transformID, mtx );
}

//----------------------------------------------------------------//
void MOAIGfxMtxCache::SetMtx ( u32 transformID, const ZLAffine3D& transform ) {

	ZLMatrix4x4 mtx;
	mtx.Init ( transform );
	this->SetMtx ( transformID, mtx );
}

//----------------------------------------------------------------//
void MOAIGfxMtxCache::SetMtx ( u32 transformID, const ZLMatrix4x4& mtx ) {

	u32 dirtyMask = 0;

	switch ( transformID ) {
	
		case PROJ_MTX:
		
			dirtyMask = PROJ_MTX_DIRTY_MASK;
			break;
			
		case UV_MTX:
		
			dirtyMask = UV_MTX_DIRTY_MASK;
			break;
			
		case VIEW_MTX:
		
			dirtyMask = VIEW_MTX_DIRTY_MASK;
			break;
			
		case WORLD_MTX:
		
			dirtyMask = WORLD_MTX_DIRTY_MASK;
			break;
	
		case INVERSE_PROJ_MTX:
		case INVERSE_UV_MTX:
		case INVERSE_VIEW_MTX:
		case INVERSE_VIEW_PROJ_MTX:
		case INVERSE_WORLD_MTX:
		case INVERSE_WORLD_VIEW_MTX:
		case INVERSE_WORLD_VIEW_PROJ_MTX:
		case VIEW_PROJ_MTX:
		case WORLD_VIEW_MTX:
		case WORLD_VIEW_PROJ_MTX:
		
			assert ( false ); // read only
			return;
	}
	
	if ( !this->mVertexTransforms [ transformID ].IsSame ( mtx )) {
		this->mVertexTransforms [ transformID ] = mtx;
		this->mDirtyFlags |= dirtyMask;
	}
}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetUVTransform () {
//
//	ZLMatrix4x4 mtx;
//	mtx.Ident ();
//	this->SetUVTransform ( mtx );
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetUVTransform ( const ZLAffine3D& transform ) {
//
//	ZLMatrix4x4 mtx;
//	mtx.Init ( transform );
//	this->SetUVTransform ( mtx );
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetUVTransform ( const ZLMatrix4x4& transform ) {
//
//	if ( !this->mUVTransform.IsSame ( transform )) {
//		this->mUVTransform = transform;
//		this->UpdateUVMtx ();
//	}
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetVertexMtxMode ( u32 input, u32 output ) {
//	
//	if (( this->mVertexMtxInput != input ) || ( this->mVertexMtxOutput != output )) {
//
//		this->mVertexMtxInput = input;
//		this->mVertexMtxOutput = output;
//		
//		// Invalidate the lower level matrices (i.e. modelview, etc) matrix in this case to force recalc
//		for ( u32 i = input; i < output; ++i ) {
//			this->mCpuVertexTransformCache [ i ] = false;
//		}
//		
//		this->UpdateCpuVertexMtx ();
//	}
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetVertexTransform ( u32 id ) {
//
//	ZLMatrix4x4 mtx;
//	mtx.Ident ();
//	this->SetVertexTransform ( id, mtx );
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetVertexTransform ( u32 id, const ZLAffine3D& transform ) {
//
//	ZLMatrix4x4 mtx;
//	mtx.Init ( transform );
//	this->SetVertexTransform ( id, mtx );
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::SetVertexTransform ( u32 id, const ZLMatrix4x4& transform ) {
//
//	assert ( id < TOTAL_VTX_TRANSFORMS );
//
//	if ( !this->mVertexTransforms [ id ].IsSame ( transform )) {
//
//		this->mVertexTransforms [ id ] = transform;
//		
//		// check to see if this is a CPU or GPU matrix and update accordingly
//		if ( id < this->mVertexMtxOutput ) {
//		
//			// Invalidate the lower level matrices (i.e. modelview, etc) matrix in this case to force recalc
//			for ( u32 i = this->mVertexMtxInput; i <= id; ++i ) {
//				this->mCpuVertexTransformCache [ i ] = false;
//			}
//			this->UpdateCpuVertexMtx ();
//		}
//	}
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::UpdateCpuVertexMtx () {
//	
//	// Used signed, so we can roll "under" to -1 without an extra range check
//	int start = this->mVertexMtxInput;
//	int finish = this->mVertexMtxOutput;
//
//	// The matrices are being multiplied A*B*C, but the common case is that
//	// B and C are static throughout all/most of a frame. Thus, we can
//	// capitalize on the associativity of matrix multiplication by caching
//	// (B*C) and save a matrix mult in the common case (assuming they haven't
//	// changed since the last update request).
//
//	int i = finish - 1;
//	
//	if ( this->mCpuVertexTransformCache [ i ]) {
//		while ( i >= start && this->mCpuVertexTransformCache [ i ]) {
//			--i;
//		}
//		this->mCpuVertexTransformMtx = this->mCpuVertexTransformCacheMtx [ i + 1 ];
//	}
//	else {
//		this->mCpuVertexTransformMtx.Ident ();
//	}
//	
//	for ( ; i >= start; --i ) {
//		this->mCpuVertexTransformMtx.Prepend ( this->mVertexTransforms [ i ]);
//		this->mCpuVertexTransformCacheMtx [ i ] = this->mCpuVertexTransformMtx;
//		this->mCpuVertexTransformCache [ i ] = true;
//	}
//
//	this->mCpuVertexTransform = !this->mCpuVertexTransformMtx.IsIdent ();
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::UpdateUVMtx () {
//
//	if ( this->mUVMtxOutput == UV_STAGE_TEXTURE ) {
//	
//		this->mCpuUVTransform = !this->mUVTransform.IsIdent ();
//	}
//	else {
//	
//		this->mCpuUVTransform = false;
//	}
//}

//----------------------------------------------------------------//
//void MOAIGfxMtxCache::UpdateViewVolume () {
//
//	ZLMatrix4x4 invViewProj;
//	invViewProj.Inverse ( this->GetMtx ( VIEW_PROJ_MTX ));
//	this->mViewVolume.Init ( invViewProj );
//}
