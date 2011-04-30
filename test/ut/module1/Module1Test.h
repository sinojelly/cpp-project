#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>

#include <module1/module1.h>


FIXTURE(Module1Test)
{
	SETUP()
	{
	}
	
	TEARDOWN()
	{
	}
	
	TEST(1 add 2 => 3)
	{
		ASSERT_EQ(3, add(1, 2));
	}
};
