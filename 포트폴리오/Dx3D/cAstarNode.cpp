#include "stdafx.h"
#include "cAstarNode.h"


cAstarNode::cAstarNode()
	: F(0.0f)
	, G(0.0f)
	, H(0.0f)
	, m_pParent(NULL)
	, m_isClose(false)
	, m_isOpen(false)
	, m_vPosition(0, 0, 0)
	, m_nHeapIndex(0)
{
}


cAstarNode::~cAstarNode()
{
}
