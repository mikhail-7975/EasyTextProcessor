#include <gtest/gtest.h>
#include "../TextProcesor/cmdCreator.h"
#include "../TextProcesor/Invoker.h"
#include "../TextProcesor/document.h"
#include "../TextProcesor/command.h"
#include <sstream>

TEST(InsertTest, emptyDoc) {
	{
		std::unique_ptr<Document> doc_(new Document);
		//std::unique_ptr<Document> doc(new Document);
		Invoker inv(doc_.get());
		std::istringstream inp{ "\"111\" 0" };
		inv.Do("insert", inp);
		EXPECT_EQ(doc_->data(), "111");
	}
}

TEST(InsertTest, notEmptyDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp{ "\"111\" 0" };
	inv.Do("insert", inp);
	std::istringstream inp2{ "\"222\" 0" };
	inv.Do("insert", inp2);
	EXPECT_EQ(doc->data(), "222111");
}

TEST(InsertTest, outOfDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp{ "\"111\" 10" };
	inv.Do("insert", inp);
	EXPECT_EQ(doc->data(), "111");
}

TEST(DeleteTest, emptyDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp{ "1 4" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc->data(), "");
}

TEST(DeleteTest, notEmptyDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 2" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc->data(), "111");
}

TEST(DeleteTest, swapIndexes) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "2 0" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc->data(), "111");
}

TEST(DeleteTest, equalIndexes) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 0" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc->data(), "22111");
}

TEST(DeleteTest, outOfDocIndex) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "10 20" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc->data(), "222111");
}

TEST(CopyPasteTest, emptyDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp{ "0 2" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "");
	std::istringstream inp3{ "6" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "");
}

TEST(CopyPasteTest, normalTest) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 2" };
	inv.Do("copy", inp);
	ASSERT_EQ(doc->buffer(), "222");
	std::istringstream inp3{ "6" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "222111222");
}

TEST(CopyPasteTest, outOfDocIndexes) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "-5 10" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "222111");
	std::istringstream inp3{ "-5" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "222111222111");
}

TEST(CopyPasteTest, swapIndexes) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "2 0" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "222");
	std::istringstream inp3{ "6" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "222111222");
}

TEST(CopyPasteTest, equalIndexes) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "3 3" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "1");
	std::istringstream inp3{ "0" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "1222111");
}

TEST(UndoTest, emptyDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	EXPECT_NO_THROW(inv.Undo());
}

TEST(UndoTest, normalTest) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 2" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "222");
	std::istringstream inp3{ "6" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "222111222");
	inv.Undo();
	EXPECT_EQ(doc->data(), "222111");
}

TEST(RedoTest, emptyDoc) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	EXPECT_NO_THROW(inv.Redo());
}

TEST(RedoTest, noUndoTest) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 2" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "222");
	std::istringstream inp3{ "6" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "222111222");
	EXPECT_NO_THROW(inv.Redo());
	EXPECT_EQ(doc->data(), "222111222");
}

TEST(RedoTest, normalTest) {
	std::unique_ptr<Document> doc(new Document);
	Invoker inv(doc.get());
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 2" };
	inv.Do("copy", inp);
	EXPECT_EQ(doc->buffer(), "222");
	std::istringstream inp3{ "6" };
	inv.Do("paste", inp3);
	EXPECT_EQ(doc->data(), "222111222");
	inv.Undo();
	EXPECT_EQ(doc->data(), "222111");
	inv.Redo();
	EXPECT_EQ(doc->data(), "222111222");
}