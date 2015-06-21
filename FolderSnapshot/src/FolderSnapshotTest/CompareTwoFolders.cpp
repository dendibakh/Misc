#include "stdafx.h"
#include "testUtil.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace boost::filesystem;

namespace FolderSnapshotTest
{
	[TestClass]
	public ref class CompareTwoFolders
	{
	public: 
		[TestMethod]
		void TestCompareTwoFolders()
		{
			path curFolderPath = TestFolderPath + "TestCompareTwoFolders\\";
			path equal1 = curFolderPath.string() + "Equal1\\";
			path equal2 = curFolderPath.string() + "Equal2\\";
			path NotEqual1 = curFolderPath.string() + "NotEqual1\\";
			path NotEqual2 = curFolderPath.string() + "NotEqual2\\";
			path NotEqual3 = curFolderPath.string() + "NotEqual3\\";
			path NotEqual4 = curFolderPath.string() + "NotEqual4\\";
			path NotEqual5 = curFolderPath.string() + "NotEqual5\\";
			Assert::IsTrue(compareTwoDirectories(equal1, equal2));
			Assert::IsFalse(compareTwoDirectories(NotEqual1, NotEqual2));
			Assert::IsFalse(compareTwoDirectories(NotEqual1, NotEqual3));
			Assert::IsFalse(compareTwoDirectories(NotEqual1, NotEqual4));
			Assert::IsFalse(compareTwoDirectories(NotEqual1, NotEqual5));
		}
	};
}
