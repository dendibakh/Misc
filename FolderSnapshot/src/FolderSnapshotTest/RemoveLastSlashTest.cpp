#include "stdafx.h"
#include "util.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace boost::filesystem;

namespace FolderSnapshotTest
{
	[TestClass]
	public ref class RemoveLastSlashTest
	{
	public: 
		[TestMethod]
		void TestRemoveLastSlash()
		{
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage\\"));
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage/"));
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage//"));
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage\\\\"));
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage////"));
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage//\\//\\"));
			Assert::IsTrue(path("G:\\Storage") == removeLastSlash("G:\\Storage"));
		}
	};
}
