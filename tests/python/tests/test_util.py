import base
import hawkey
import unittest

class Util(unittest.TestCase):
    def test_chksum_name(self):
        name = hawkey.chksum_name(hawkey.CHKSUM_SHA256)
        self.assertEqual(name, "sha256")

    def test_chksum_type(self):
        t = hawkey.chksum_type("SHA1")
        self.assertEqual(t, hawkey.CHKSUM_SHA1)
        self.assertRaises(ValueError, hawkey.chksum_type, "maID")

    def test_split_nevra(self):
        self.assertRaises(hawkey.ValueException, hawkey.split_nevra, "no.go")
        self.assertRaises(hawkey.ValueException, hawkey.split_nevra, "")

        nevra = hawkey.split_nevra("eyes-8:1.2.3-4.fc18.x86_64")
        self.assertEqual(nevra.name, "eyes")
        self.assertEqual(nevra.epoch, 8)
        self.assertEqual(nevra.version, "1.2.3")
        self.assertEqual(nevra.release, "4.fc18")
        self.assertEqual(nevra.arch, "x86_64")

class UtilWithSack(base.TestCase):
    def setUp(self):
        self.sack = hawkey.test.TestSack(repo_dir=self.repo_dir)
        self.sack.load_system_repo()

    def test_nevra_to_query(self):
        nevra = hawkey.split_nevra("baby-6:5.0-11.x86_64")
        q = nevra.to_query(self.sack)
        self.assertLength(q, 1)
        pkg = str(q[0])
        self.assertEqual(pkg, "baby-6:5.0-11.x86_64")
