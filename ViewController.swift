//
//  ViewController.swift
//  pg02_with_libpq
//
//  Created by Tim on 2016/6/26.
//  Copyright © 2016 Tim. All rights reserved.
//  //https://github.com/djthorpe/postgresql-kit/releases

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        // This is the data gonna insert to SQL you can adjust that base what you need.
        let obj_id: String = "ios025442"
        let obj_time: String = "2016012301"
        let obj_userloc: String = "120.35685,23.59027"
        let obj_keyword: String = "KeyWorld"
        let obj_selectresult: String = "xxxx"
        let obj_selectloc: String = "120.35685,23.59027"
        
        // Change string type for C API
        // http://goo.gl/tO9CuF
        let id: [CChar]? = obj_id.cStringUsingEncoding(NSUTF8StringEncoding)
        let time: [CChar]? = obj_time.cStringUsingEncoding(NSUTF8StringEncoding)
        let userloc: [CChar]? = obj_userloc.cStringUsingEncoding(NSUTF8StringEncoding)
        let keyword: [CChar]? = obj_keyword.cStringUsingEncoding(NSUTF8StringEncoding)
        let selectresult: [CChar]? = obj_selectresult.cStringUsingEncoding(NSUTF8StringEncoding)
        let selectloc: [CChar]? = obj_selectloc.cStringUsingEncoding(NSUTF8StringEncoding)
        
        // send data to C API function "mainConn"
        mainConn(UnsafeMutablePointer<Int8>(id!),UnsafeMutablePointer<Int8>(time!),UnsafeMutablePointer<Int8>(userloc!),UnsafeMutablePointer<Int8>(keyword!),UnsafeMutablePointer<Int8>(selectresult!),UnsafeMutablePointer<Int8>(selectloc!))
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

