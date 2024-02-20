importScripts("mdflibjs.js");

onmessage = function(e) {
    const f = e.data[0];

    FS.mkdir('/work');
    FS.mount(WORKERFS, { files: [f] }, '/work');

    console.log("Initializing reader for file: " + f.name);
    const Reader = new Module.Reader('/work/' + f.name);

    Reader.readEverythingButData();
    const Header = Reader.getHeader();
    console.log("Author: " + Header.getAuthor());
    console.log("Department: " + Header.getDepartment());
    console.log("Description: " + Header.getDescription());
    console.log("Project: " + Header.getProject());
    console.log("StartTime: " + Header.getStartTime());
    console.log("Subject: " + Header.getSubject());

    console.log("Finished reading: " + f.name);

    FS.unmount('/work');
    FS.rmdir('/work');
}
