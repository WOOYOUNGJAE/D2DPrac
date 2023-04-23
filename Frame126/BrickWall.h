#pragma once
#include "BrickBase.h"
class CBrickWall : public CBrickBase
{
public:
	CBrickWall();
	virtual ~CBrickWall() override = default;


public:
	bool Update() override;
};

