//
//  ViewController.swift
//  ECGv1
//
//  Created by Bobby Rouse on 2/14/22.
//

import UIKit
import CoreBluetooth

class ViewController: UIViewController, CBPeripheralDelegate, CBCentralManagerDelegate {
    
    // Properties for Bluetooth
    private var centralManager: CBCentralManager!
    private var peripheral: CBPeripheral!
    
    private let imageView: UIImageView = {
       let imageView = UIImageView()
        imageView.contentMode = .scaleAspectFill
        imageView.backgroundColor = .gray
        
       return imageView
    }()
    
    //start button
    public let button1: UIButton = {
       let button1 = UIButton()
        button1.backgroundColor = .gray
        button1.setTitle("Start Reading", for: .normal)
        button1.setTitleColor(.black, for: .normal)
       return button1
    }()
    
    //heart rate value
    public let button2: UIButton = {
       let button2 = UIButton()
        button2.backgroundColor = .gray
        button2.setTitle("72", for: .normal)
        button2.setTitleColor(.black, for: .normal)
       return button2
    }()
    
    //Lead Status value
    public let button3: UIButton = {
       let button3 = UIButton()
        button3.backgroundColor = .gray
        button3.setTitle("OK", for: .normal)
        button3.setTitleColor(.black, for: .normal)
       return button3
    }()
    
    //global vars for heartbeat sim
    var testindex: Int = 0
    var timer: Timer?
    var photoindex: Int = 0
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Bluetooth Central manager
        
        //view.backgroundColor = .systemGray
        view.addSubview(imageView)
        imageView.frame = CGRect(x: (view.frame.size.width-300)/2, y: 300, width: 300, height: 300)
        //imageView.frame = CGRect(x: 0, y: 0, width: 300, height: 300)
        //imageView.center = view.center
        
        
        view.addSubview(button1)
        view.addSubview(button2)
        view.addSubview(button3)
        
        getPhoto()
        
        button1.addTarget(self, action: #selector(didTapButton1), for: .touchUpInside)
    }
  
    
    @objc func refresh(){
        if( testindex > 20){
            timer?.invalidate()
        }
        //photo gen
        getPhoto()
        
        //random/realistic heartbeat
        var n = Int.random(in: 70...90)
        button2.setTitle(String(n), for: .normal)
        
        //index for timer stoppage
        testindex = testindex+1
    }
   
    @objc func didTapButton1() {
        timer = Timer.scheduledTimer(withTimeInterval: 1, repeats: true, block: { _ in
            self.refresh()
        })
        
        //getPhoto()
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        button1.frame = CGRect(
            x: 30,
            y: view.frame.size.height-150-view.safeAreaInsets.bottom,
            width: view.frame.size.width-60,
            height: 55
        )
        button2.frame = CGRect(
            x: 57,
            y: 225,
            width: 60,
            height: 55
        )
        button3.frame = CGRect(
            x: view.frame.size.width - 117,
            y: 225,
            width: 60,
            height: 55
        )
        
    }
    
    func getPhoto(){
       /* let urlString = "https://source.unsplash.com/random/600x600"
        
        let url = URL(string:urlString)!
        guard let data = try? Data(contentsOf: url) else {
            return
        }*/
        
        if (photoindex == 0){
            imageView.image = UIImage(named: "hb1")
            photoindex = photoindex+1
        }else if(photoindex==1){
            imageView.image = UIImage(named: "hb2")
            photoindex = photoindex+1
        }else if(photoindex==2){
            imageView.image = UIImage(named: "hb3")
            photoindex = photoindex+1
        }else if(photoindex==3){
            imageView.image = UIImage(named: "hb4")
            photoindex = photoindex+1
        }else if(photoindex==4){
            imageView.image = UIImage(named: "hb5")
            photoindex = photoindex+1
        }else if(photoindex==5){
            imageView.image = UIImage(named: "hb6")
            photoindex = photoindex+1
        }else if(photoindex==6){
            imageView.image = UIImage(named: "hb7")
            photoindex = photoindex+1
        }else if(photoindex==7){
            imageView.image = UIImage(named: "hb8")
            photoindex = 0
        }
        
        //imageView.image = UIImage(named: "hb1")
    }

}

